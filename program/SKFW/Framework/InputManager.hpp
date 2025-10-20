#pragma once
#include<unordered_map>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SKFW/Framework/Singleton.hpp>

//	�L�[�̏��
enum KeyState {
	none,
	pressed,
	held,
	released,
};

/// <summary>
/// ���͊Ǘ��N���X�Asfml������͏�Ԃ������Ă��ăt���[�����Ƃɍs���B
/// </summary>
class InputManager : public Singleton<InputManager> {
	//	�}�E�X�̏��
	struct MouseState {
		sf::Vector2i position;
		KeyState left = KeyState::none;
		KeyState right = KeyState::none;
	};

	//	�L�[�̓��͏�Ԏ擾
	KeyState GetKeyState(sf::Keyboard::Key key)const {
		auto it = m_keyStates.find(key);
		if (it != m_keyStates.end()) return it->second;
		return KeyState::none;
	}

public:

	//	�t���[������
	void Update() {
		//	�L�[��Ԃ𒷉����������Ă����ԂɕύX
		for (auto& [key, state] : m_keyStates) {
			if (state == KeyState::pressed) state = KeyState::held;
			else if (state == KeyState::released) state = KeyState::none;
		}

		//	��
		if (m_mouse.left == KeyState::pressed) m_mouse.left = KeyState::held;
		else if (m_mouse.left == KeyState::released) m_mouse.left = KeyState::none;

		//	�E
		if (m_mouse.right == KeyState::pressed) m_mouse.right = KeyState::held;
		if (m_mouse.right == KeyState::released) m_mouse.right = KeyState::none;
	}

	//	���͏�Ԃ̍X�V
	void ProcessEvent(const sf::Event& event) {
		//	==========�L�[�{�[�h==========
		//	����
		if (event.is<sf::Event::KeyPressed>()) {
			const auto* key = event.getIf<sf::Event::KeyPressed>();
			if (key) {
				auto& state = m_keyStates[key->code];
				if (state != KeyState::held) {
					state = KeyState::pressed;
				}
			}
		}
		//	����
		else if (event.is<sf::Event::KeyReleased>()) {
			const auto* key = event.getIf<sf::Event::KeyReleased>();
			if (key) m_keyStates[key->code] = KeyState::released;
		}

		//	==========�}�E�X==========
		//	����
		else if (event.is<sf::Event::MouseButtonPressed>()) {
			const auto* m = event.getIf<sf::Event::MouseButtonPressed>();
			if (m) {
				if (m->button == sf::Mouse::Button::Left) m_mouse.left = KeyState::pressed;
				else if (m->button == sf::Mouse::Button::Right) m_mouse.right = KeyState::pressed;
			}
		}
		//	����
		else if (event.is<sf::Event::MouseButtonReleased>()) {
			const auto* m = event.getIf<sf::Event::MouseButtonReleased>();
			if (m) {
				if (m->button == sf::Mouse::Button::Left) m_mouse.left = KeyState::released;
				else if (m->button == sf::Mouse::Button::Right)m_mouse.right = KeyState::released;
			}
		}
		//	�}�E�X�ړ�
		else if (event.is<sf::Event::MouseMoved>()) {
			const auto* m = event.getIf<sf::Event::MouseMoved>();
			if (m) m_mouse.position = m->position;
		}

	}

	//	-----�L�[����----- //
	//	�������u�Ԃ���true
	bool IsKeyPressed(sf::Keyboard::Key key)const {
		return GetKeyState(key) == KeyState::pressed;
	}

	//	�����Ă����true
	bool IsKeyHeld(sf::Keyboard::Key key)const {
		return GetKeyState(key) == KeyState::held;
	}

	//	�������u��
	bool IsKeyReleased(sf::Keyboard::Key key)const {
		return GetKeyState(key) == KeyState::released;
	}

	//	�ǂꂩ�̃L�[��������Ă�����true
	bool IsAnyKeyDown()const {
		for (auto& [_, state] : m_keyStates) {
			if (state == KeyState::pressed || state == KeyState::held) return true;
		}
		return false;
	}

	//	-----�}�E�X----- //
	//	�������u�Ԃ���true
	bool IsMousePressed(sf::Mouse::Button btn)const {
		if (btn == sf::Mouse::Button::Left) return m_mouse.left == KeyState::pressed;
		if (btn == sf::Mouse::Button::Right) return m_mouse.right == KeyState::pressed;
		return false;
	}

	//	�����Ă����true
	bool IsMouseHeld(sf::Mouse::Button btn) const {
		if (btn == sf::Mouse::Button::Left) return m_mouse.left == KeyState::held;
		if (btn == sf::Mouse::Button::Right) return m_mouse.right == KeyState::held;
		return false;
	}

	//	�������u��true
	bool IsMouseReleased(sf::Mouse::Button btn) const {
		if (btn == sf::Mouse::Button::Left) return m_mouse.left == KeyState::released;
		if (btn == sf::Mouse::Button::Right) return m_mouse.right == KeyState::released;
		return false;
	}

	//	���W
	const sf::Vector2i& GetMousePosition() const { return m_mouse.position; }



private:
	std::unordered_map<sf::Keyboard::Key, KeyState> m_keyStates;	//	�L�[�̓��͏��
	MouseState m_mouse;	//	�}�E�X�̏��\����
};

