#pragma once
#include "GamePlay/Components/IComponent.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/GameObject.h"


/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class EnemyBehaviour : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<EnemyBehaviour> Sptr;

	EnemyBehaviour();
	virtual ~EnemyBehaviour();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;



	float StartVelocity;
private:
	float Range;
	float _desiredVelocity;
	float _maxVelocity;
	
	glm::vec3 _movementVector, ArrivalVector, RangeVec;
	glm::vec3 _startPosiiton;
	size_t m_segmentIndex = 0;
	
public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(EnemyBehaviour);
	virtual nlohmann::json ToJson() const override;
	static EnemyBehaviour::Sptr FromJson(const nlohmann::json& blob);

	std::weak_ptr<Gameplay::GameObject> player;

	float m_segmentTravelTime = 4.0f;


	


	
protected:
	
	float _timer = 0.0f;

	float _playbackSpeed;
	float _impulse;
	bool _playerInTrigger = false;
	Gameplay::Physics::RigidBody::Sptr _body;
};