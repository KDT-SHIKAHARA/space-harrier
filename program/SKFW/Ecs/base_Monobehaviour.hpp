#pragma once
#include<SKFW/Ecs/base_component.hpp>

/// <summary>
/// 自作のコンポーネントの基底クラス
/// </summary>
class IMonoBehaviour : public IComponent
{
public:
	virtual ~IMonoBehaviour() = default;
	virtual void Initialize() {}
	virtual void Update(float dt) {}
	virtual void FixedUpdate(float fixedDt) {}
	virtual void Reset() {}

};
