#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <variant>
#include <format>

struct Div_T;
struct Input_T;
struct Button_T;
using Widget = std::variant<std::unique_ptr<Div_T>, std::unique_ptr<Button_T>, std::unique_ptr<Input_T>, std::string>;

struct WidgetList {
	WidgetList() = default;
	template<typename ...Args>
	constexpr WidgetList(Args&&... args) noexcept {
		data.reserve(sizeof...(args));
		(data.emplace_back(std::move(args)), ...);
	}

	std::vector<Widget> data;
};

struct Div_T {
	static constexpr std::string_view tag_name = "div";
	WidgetList children;
	std::string className;
	void (*onClick)(void) = nullptr;
};

struct Button_T {
	static constexpr std::string_view tag_name = "button";
	WidgetList children;
	std::string className;
	void (*onClick)(void) = nullptr;
};

struct Input_T {
	static constexpr std::string_view tag_name = "input";
	WidgetList children;
	std::string className;
	void (*onChange)(const std::string&) = nullptr;
};

inline auto Div(Div_T&& d) {
	return std::make_unique<Div_T>(std::move(d));
};

inline auto Button(Button_T&& b) {
	return std::make_unique<Button_T>(std::move(b));
};

inline auto Input(Input_T&& d) {
	return std::make_unique<Input_T>(std::move(d));
};

struct StringifyVisitor {
	std::string operator()(const std::string& s) {
		return s;
	}
	std::string operator()(const auto& widget) {
		std::string out = std::format("<{} class=\"{}\">\n", widget->tag_name, widget->className);
		for (const Widget& w : widget->children.data) {
			out += std::visit(*this, w);
		}
		out += std::format("\n</{}>\n", widget->tag_name);

		return out;
	}
};

inline std::string build_html(const Widget& w) {
	return std::visit(StringifyVisitor{}, w);
}

