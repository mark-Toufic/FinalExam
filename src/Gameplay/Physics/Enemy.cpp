#include "Gameplay/Physics/Enemy.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/Components/TriggerVolumeEnterBehaviour.h"
using namespace std;
void EnemyBehaviour::Awake()
{

	_body = GetComponent<Gameplay::Physics::RigidBody>();

	if (_body == nullptr) {
		_playerInTrigger = false;
		_startPosiiton = GetGameObject()->GetPosition();
	}
}


void EnemyBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &_impulse, 1.0f);
}

nlohmann::json EnemyBehaviour::ToJson() const {
	return {
		{ "impulse", _impulse }
	};
}

EnemyBehaviour::EnemyBehaviour() :
	IComponent(),
	_impulse(10.0f)
{ }


EnemyBehaviour::Sptr EnemyBehaviour::FromJson(const nlohmann::json& blob) {
	EnemyBehaviour::Sptr result = std::make_shared<EnemyBehaviour>();
	result->_impulse = blob["impulse"];
	return result;
}

template<typename T>
T Lerp(const T& a, const T& b, float t)
{
	return (1.0f - t) * a + t * b;
}

extern float playerX, playerY, playerZ;


EnemyBehaviour::~EnemyBehaviour() = default;

float deathTime1 = 0;



// Code below has been taken from Hoepful goats enemy script mad by Mark Toufic and COlin Charleson
void EnemyBehaviour::Update(float deltaTime)
{
	
	
		
			if ((sqrt(pow(GetGameObject()->GetPosition().x - playerX, 2) + pow(GetGameObject()->GetPosition().y - playerY, 2) * 2)) <= 4)
			{


				if (GetGameObject()->GetPosition().x > playerX)
				{
					GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x - 0.01, GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z));
				}

				if (GetGameObject()->GetPosition().y > playerY)
				{
					GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - 0.01, GetGameObject()->GetPosition().z));
				}
				if (GetGameObject()->GetPosition().z > playerZ)
				{
					GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y , GetGameObject()->GetPosition().z - 0.01));
				}

				if (GetGameObject()->GetPosition().x < playerX)
				{
					GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x + 0.01, GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z));
				}

				if (GetGameObject()->GetPosition().y < playerY)
				{
					GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + 0.01, GetGameObject()->GetPosition().z));
				}
				if (GetGameObject()->GetPosition().z < playerZ)
				{
					GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y , GetGameObject()->GetPosition().z + 0.01));
				}

		

				GetGameObject()->LookAt(glm::vec3(playerX, playerY, 0));

			
				if ((sqrt(pow(GetGameObject()->GetPosition().x - playerX, 1) + pow(GetGameObject()->GetPosition().z - playerZ,1) * 1)) > 0.8)
				{
					cout << "lose" << endl;
				}

			}

			else if (playerX <= -25)
			{
				cout << "win" << endl;
			}

			else
			{
				std::vector<glm::vec3> _points = { glm::vec3(-9.0f, 0, 4.0f), glm::vec3(-3.0f, 0, 4.0f), };

				_timer += deltaTime;

				while (_timer >= m_segmentTravelTime)
				{
					_timer -= m_segmentTravelTime;

					m_segmentIndex += 1;

					if (m_segmentIndex == _points.size())
					{
						m_segmentIndex = 0;
					}
				}

				float t = _timer / m_segmentTravelTime;

				glm::vec3 a = _points[((m_segmentIndex - 1) + _points.size()) % _points.size()];
				glm::vec3 b = _points[((m_segmentIndex)+_points.size()) % _points.size()];

				GetGameObject()->SetPostion(Lerp(a, b, t));
				GetGameObject()->LookAt(glm::vec3(b.x, b.y, 0));
			}
			

}

