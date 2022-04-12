#include "2d/CCSpriteChunk.h"

#include "2d/CCSprite.h"
#include "2d/CCCamera.h"
#include "2d/CCTMXLayer.h"
#include "base/ccTypes.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

SpriteChunk* SpriteChunk::create()
{
	SpriteChunk *spriteChunk = new (std::nothrow) SpriteChunk();
	if (spriteChunk && spriteChunk->init())
	{
		spriteChunk->autorelease();
		return spriteChunk;
	}
	CC_SAFE_DELETE(spriteChunk);
	return nullptr;
}

bool SpriteChunk::init()
{
	return true;
}


Rect SpriteChunk::getRect() const {
	return _rect;
}



// MARK: visit, draw, transform

void SpriteChunk::addShell(std::shared_ptr<SpriteShell> shell){
	_shells.push_back(shell);
	
	_rect.origin = cocos2d::Vec2(shell->_position.x, shell->_position.y);
	_rect.size = cocos2d::Size(0, 0);
	
	for(auto& child : _shells){
		_rect.origin.x = std::min(_rect.origin.x, child->_position.x);
		_rect.origin.y = std::min(_rect.origin.y, child->_position.y);
	}
	
	for(auto& child : _shells){
		auto childRect = Rect(child->_position.x, child->_position.y, child->_size.width, child->_size.height);
		_rect.merge(childRect);
	}
	
	setPosition(_rect.origin);
	setContentSize(Size(_rect.size.width, _rect.size.height));
}

void SpriteChunk::removeShell(int uid){
	_shells[uid] = {};
}

void SpriteChunk::setShellPool(std::reference_wrapper<std::unordered_map<int, cocos2d::Sprite*>> pool){
	_pool = pool;
}

int SpriteChunk::getShellCount() const {
	return _shells.size();
}

void SpriteChunk::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	// quick return if not visible. children won't be drawn.
	if (!_visible)
	{
		return;
	}
	
	uint32_t flags = processParentFlags(parentTransform, parentFlags);
	
	
	bool visibleByCamera = isVisitableByVisitingCamera();
	
	int i = 0;
	
	if(!_shells.empty())
	{
		sortAllChildren();
		// self draw
		if (visibleByCamera){
			
			bool insideBounds = true;
			// Don't calculate the culling if the transform was not updated
			auto visitingCamera = Camera::getVisitingCamera();
			auto defaultCamera = Camera::getDefaultCamera();
			if (visitingCamera == nullptr)
				insideBounds = true;
			else if (visitingCamera == defaultCamera)
				insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY) || visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(_modelViewTransform, _contentSize) : insideBounds;
			else
				// XXX: this always return true since
				insideBounds = renderer->checkVisibility(_modelViewTransform, _contentSize);

			if(insideBounds){
				this->draw(renderer, _modelViewTransform, flags);
			}
			
		}
	}
}

// draw
void SpriteChunk::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	for(auto shell : _shells){
	
		auto pooledSprite = _pool.get()[shell->_gid];
		pooledSprite->setPosition(shell->_position - _rect.origin);
		pooledSprite->setAnchorPoint(shell->_anchor);
		pooledSprite->setRotation(shell->_rotation);
		pooledSprite->setOpacity(shell->_opacity);
		pooledSprite->setFlippedX(shell->_flippedX);
		pooledSprite->setFlippedY(shell->_flippedY);
		
		pooledSprite->setVisible(true);
		pooledSprite->setCustomTrianglesCommand(shell->_trianglesCommand);
		pooledSprite->visit(renderer, transform, flags);
		pooledSprite->setVisible(false);

	}
}


SpriteChunk::SpriteChunk() : _rect(0, 0, 0, 0), _pool(_dummyPool)
{

}

SpriteChunk::~SpriteChunk()
{
}


NS_CC_END
