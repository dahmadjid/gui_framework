#include "comp.hpp"
#include <iostream>

Widget blue_button(const std::string& text) {
	return Button({
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
