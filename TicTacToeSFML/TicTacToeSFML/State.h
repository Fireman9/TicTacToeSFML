#pragma once
namespace Sonar {
	class State {
	public:
		virtual void Init() = 0;

		virtual void handleInput() = 0;
		virtual void update(float dt) = 0;
		virtual void draw(float data) = 0;

		virtual void pause() {

		}
		virtual void resume() {

		}
	};
}