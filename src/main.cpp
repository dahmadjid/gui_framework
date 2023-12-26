#include "GuiFramework.hpp"
#include <webview.h>
#ifdef _WIN32
#include <windows.h>
#include <dwmapi.h>
#endif

Widget blue_button(const std::string& text) {
	return Button(Button_T{
		.children = text,
		.className = "bg-blue-500"
	});
}


Widget red_button(const std::string& text) {
	return Button({
		.children = text,
		.className = "bg-red-500"
	});
}

Widget component() {
	return Div({
		.children = WidgetList(
			Div({
				.children = "Hello World"
			}),
			red_button("Red Button"),
			blue_button("Blue Button")
		),
		.className = "font-bold",
		.onClick = [] {
			std::cout << "Hello World\n";
		},
	});
}


int main() {
	webview::webview w(false, nullptr);
	w.set_title("Basic Example");
	w.set_size(480, 320, WEBVIEW_HINT_NONE);
	w.set_html(build_html(component()));
	w.run();
	return 0;
}