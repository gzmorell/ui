// Copyright (c) 2017 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// Compilable source code snippets that are used in documentation.

#include <boost/config.hpp>

#include <chrono>

/// [include]
#include <boost/ui.hpp>
/// [include]

/// [namespace]
namespace ui = boost::ui;
/// [namespace]

/// [button]
class button_dialog : public ui::dialog
{
public:
    button_dialog() : ui::dialog("Button usage dialog")
    {
        ui::button(*this, "&Press me")
            .on_press(&button_dialog::on_press_me, this);

        show_modal();
    }

private:
    void on_press_me()
    {
        ui::info_dialog("Hello");
    }
};
/// [button]

void run_gui()
{
    ui::dialog parent("Boost.UI documentation snippets");

    ui::vbox layout(parent);

    layout << ui::button(parent, "&button").on_press([]{ button_dialog(); });

    layout << ui::button(parent, "&Event").on_press([]
    {
/// [event]
ui::dialog dlg("Example dialog");
ui::button(dlg, "&Quit")
    .on_press(&ui::dialog::close, &dlg);
dlg.show_modal();
/// [event]
    });

    layout << ui::button(parent, "&Timeout").on_press([]
    {
/// [on_timeout]
ui::on_timeout(std::chrono::milliseconds(1000),
               []{ BOOST_UI_LOG; }
              );
/// [on_timeout]
    });

/// [string_box]
ui::string_box string_box = ui::string_box(parent, "Initial text");
string_box.on_edit([&]
{
    ui::log::info() << "Edited text: " << string_box.text();
});
/// [string_box]
    layout << string_box.layout().justify();

/// [combo_box]
ui::combo_box combo_box = ui::combo_box(parent,
    "Initial text",
    { "Option 1", "Option 2", "Option 3" })
    .on_select_event([&](ui::index_event& e)
    {
        ui::log::info() << "Selected option index: " << e.index()
                        << ", text: "                << combo_box.text();
    });
/// [combo_box]
    layout << combo_box.layout().justify();

/// [choice]
ui::choice choice = ui::choice(parent,
    { "Option 1", "Option 2", "Option 3" })
    .on_select_event([&](ui::index_event& e)
    {
        ui::log::info() << "Selected option index: " << e.index()
                        << ", text: "                << choice.text();
    });
/// [choice]
    layout << choice.layout().justify();

/// [list_box]
ui::list_box list_box = ui::list_box(parent,
    { "Option 1", "Option 2", "Option 3" })
    .on_select_event([&](ui::index_event& e)
    {
        ui::log::info() << "Selected option index: " << e.index();
    })
    .on_activate_event([&](ui::index_event& e)
    {
        ui::log::info() << "Activated option index: " << e.index();
    })
    ;
/// [list_box]
    layout << list_box.layout().justify();

    parent.resize(400, 600);
    parent.show_modal();
}

/// [main]
int ui_main()
{
    run_gui();

    return 0;
}

int main(int argc, char* argv[])
{
    return ui::entry(&ui_main, argc, argv);
}
/// [main]
