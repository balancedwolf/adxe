#pragma once


#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>


#include "2d/CCNode.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN

struct SpriteShell;

class CC_DLL SpriteChunk : public Node
{
public:

	static SpriteChunk* create();
	virtual Rect getRect() const;
	void addShell(std::shared_ptr<SpriteShell> shell);
	void removeShell(int uid);
	int getShellCount() const;
	void setShellPool(std::reference_wrapper<std::unordered_map<int, cocos2d::Sprite*>> pool);
	virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	
	CC_CONSTRUCTOR_ACCESS :
	/**
	 * @js ctor
	 */
	SpriteChunk();
	virtual ~SpriteChunk();
	virtual bool init() override;
		
private:
	CC_DISALLOW_COPY_AND_ASSIGN(SpriteChunk);
	Rect _rect;
	std::vector<std::shared_ptr<SpriteShell>> _shells;
	std::unordered_map<int, cocos2d::Sprite*> _dummyPool;
	std::reference_wrapper<std::unordered_map<int, cocos2d::Sprite*>> _pool;

};


NS_CC_END

