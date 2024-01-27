#pragma once
#include <chrono>
#include <memory>
#include <vector>
#include <variant>
#include <format>
#include "webview.h"
#ifdef _WIN32
#include <windows.h>
#include <dwmapi.h>
#endif

struct Div_T;
struct Input_T;
struct Button_T;

struct StringifyVisitor {
	inline std::string operator()(const std::string& s) const {
		return s;
	}
	inline std::string operator()(const auto& widget) const {
		return widget->render();
	}
};

template<typename... Types>
struct Widget_T: public std::variant<Types...> {
	using std::variant<Types...>::variant;

	inline std::string render() const {
		return std::visit(StringifyVisitor{}, *this);
	}
};

using Widget = Widget_T<std::unique_ptr<Div_T>, std::unique_ptr<Button_T>, std::unique_ptr<Input_T>, std::string>;



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
	WidgetList children;
	std::string className = "";
	void (*onClick)(void) = nullptr;
	inline std::string render() const {
		std::string out;
		for (const auto& w : this->children.data) {
			out += w.render();
		}
		return std::format("<div class=\"{}\">{}</div>", this->className, out);
	}
};

struct Button_T {
	WidgetList children;
	std::string className = "";
	void (*onClick)(void) = nullptr;
	inline std::string render() const {
		std::string out;
		for (const auto& w : this->children.data) {
			out += w.render();
		}
		return std::format("<button class=\"{}\">{}</button>", this->className, out);
	}
};

struct Input_T {
	static constexpr std::string_view tag_name = "input";
	WidgetList children;
	std::string className = "";
	void (*onChange)(const std::string&) = nullptr;
	inline std::string render() const {
		std::string out;
		for (const auto& w : this->children.data) {
			out += w.render();
		}
		return std::format("<input class=\"{}\">{}</input>", this->className, out);
	}
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

#include <thread>
struct Webview {
	webview::webview webview;
	Webview(): webview(false, nullptr) {
		webview.set_size(400, 400, WEBVIEW_HINT_NONE);
		webview.set_title("Application");
	}
	void update(const Widget& component) {
		std::string s = component.render();
		const auto up = [this, s]{

		};
		std::thread t(up);
		
	}
};

