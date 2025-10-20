#pragma once
#include<unordered_map>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SKFW/Framework/Singleton.hpp>

//	キーの状態
enum KeyState {
	none,
	pressed,
	held,
	released,
};

/// <summary>
/// 入力管理クラス、sfmlから入力状態を持ってきてフレームごとに行う。
/// </summary>
class InputManager : public Singleton<InputManager> {
	//	マウスの状態
	struct MouseState {
		sf::Vector2i position;
		KeyState left = KeyState::none;
		KeyState right = KeyState::none;
	};

	//	キーの入力状態取得
	KeyState GetKeyState(sf::Keyboard::Key key)const {
		auto it = m_keyStates.find(key);
		if (it != m_keyStates.end()) return it->second;
		return KeyState::none;
	}

public:

	//	フレーム末で
	void Update() {
		//	キー状態を長押しか離している状態に変更
		for (auto& [key, state] : m_keyStates) {
			if (state == KeyState::pressed) state = KeyState::held;
			else if (state == KeyState::released) state = KeyState::none;
		}

		//	左
		if (m_mouse.left == KeyState::pressed) m_mouse.left = KeyState::held;
		else if (m_mouse.left == KeyState::released) m_mouse.left = KeyState::none;

		//	右
		if (m_mouse.right == KeyState::pressed) m_mouse.right = KeyState::held;
		if (m_mouse.right == KeyState::released) m_mouse.right = KeyState::none;
	}

	//	入力状態の更新
	void ProcessEvent(const sf::Event& event) {
		//	==========キーボード==========
		//	押し
		if (event.is<sf::Event::KeyPressed>()) {
			const auto* key = event.getIf<sf::Event::KeyPressed>();
			if (key) {
				auto& state = m_keyStates[key->code];
				if (state != KeyState::held) {
					state = KeyState::pressed;
				}
			}
		}
		//	離し
		else if (event.is<sf::Event::KeyReleased>()) {
			const auto* key = event.getIf<sf::Event::KeyReleased>();
			if (key) m_keyStates[key->code] = KeyState::released;
		}

		//	==========マウス==========
		//	押し
		else if (event.is<sf::Event::MouseButtonPressed>()) {
			const auto* m = event.getIf<sf::Event::MouseButtonPressed>();
			if (m) {
				if (m->button == sf::Mouse::Button::Left) m_mouse.left = KeyState::pressed;
				else if (m->button == sf::Mouse::Button::Right) m_mouse.right = KeyState::pressed;
			}
		}
		//	離し
		else if (event.is<sf::Event::MouseButtonReleased>()) {
			const auto* m = event.getIf<sf::Event::MouseButtonReleased>();
			if (m) {
				if (m->button == sf::Mouse::Button::Left) m_mouse.left = KeyState::released;
				else if (m->button == sf::Mouse::Button::Right)m_mouse.right = KeyState::released;
			}
		}
		//	マウス移動
		else if (event.is<sf::Event::MouseMoved>()) {
			const auto* m = event.getIf<sf::Event::MouseMoved>();
			if (m) m_mouse.position = m->position;
		}

	}

	//	-----キー判定----- //
	//	押した瞬間だけtrue
	bool IsKeyPressed(sf::Keyboard::Key key)const {
		return GetKeyState(key) == KeyState::pressed;
	}

	//	押している間true
	bool IsKeyHeld(sf::Keyboard::Key key)const {
		return GetKeyState(key) == KeyState::held;
	}

	//	離した瞬間
	bool IsKeyReleased(sf::Keyboard::Key key)const {
		return GetKeyState(key) == KeyState::released;
	}

	//	どれかのキーが押されていたらtrue
	bool IsAnyKeyDown()const {
		for (auto& [_, state] : m_keyStates) {
			if (state == KeyState::pressed || state == KeyState::held) return true;
		}
		return false;
	}

	//	-----マウス----- //
	//	押した瞬間だけtrue
	bool IsMousePressed(sf::Mouse::Button btn)const {
		if (btn == sf::Mouse::Button::Left) return m_mouse.left == KeyState::pressed;
		if (btn == sf::Mouse::Button::Right) return m_mouse.right == KeyState::pressed;
		return false;
	}

	//	押している間true
	bool IsMouseHeld(sf::Mouse::Button btn) const {
		if (btn == sf::Mouse::Button::Left) return m_mouse.left == KeyState::held;
		if (btn == sf::Mouse::Button::Right) return m_mouse.right == KeyState::held;
		return false;
	}

	//	離した瞬間true
	bool IsMouseReleased(sf::Mouse::Button btn) const {
		if (btn == sf::Mouse::Button::Left) return m_mouse.left == KeyState::released;
		if (btn == sf::Mouse::Button::Right) return m_mouse.right == KeyState::released;
		return false;
	}

	//	座標
	const sf::Vector2i& GetMousePosition() const { return m_mouse.position; }



private:
	std::unordered_map<sf::Keyboard::Key, KeyState> m_keyStates;	//	キーの入力状態
	MouseState m_mouse;	//	マウスの情報構造体
};

