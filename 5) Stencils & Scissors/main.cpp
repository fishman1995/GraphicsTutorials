//#include "../nclgl/Window.h"
//#include "renderer.h"
//
//int main() {
//	Window w("Index Buffers!", 800, 600, false);
//	if (!w.HasInitialised()) {
//		return -1;
//	}
//
//	Renderer renderer(w);
//	if (!renderer.HasInitialised()) {
//		return -1;
//	}
//
//	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
//		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_1)) {
//			renderer.ToggleScissor();
//		}
//		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_2)) {
//			renderer.ToggleStencil();
//		}
//
//		renderer.RenderScene();
//		renderer.SwapBuffers();
//	}
//	return 0;
//}