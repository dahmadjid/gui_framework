#include "GuiFramework.hpp"
#include "comp.hpp"
#include "webview.h"
#include "iostream"

int main() {
	Webview w;
	w.update(component());
	w.webview.run();
}
