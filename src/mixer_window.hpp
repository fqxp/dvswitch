// Copyright 2007-2009 Ben Hutchings.
// See the file "COPYING" for licence details.

// The top-level window

#ifndef DVSWITCH_MIXER_WINDOW_HPP
#define DVSWITCH_MIXER_WINDOW_HPP

#include <sys/types.h>

#include <boost/thread/mutex.hpp>

#include <glibmm/refptr.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/separator.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/window.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scale.h>

#include "auto_pipe.hpp"
#include "dv_display_widget.hpp"
#include "dv_selector_widget.hpp"
#include "mixer.hpp"
#include "status_overlay.hpp"
#include "vu_meter.hpp"

namespace Glib
{
    class IOSource;
}

class connector;

class mixer_window : public Gtk::Window, public mixer::monitor
{
public:
    mixer_window(mixer & mixer, connector & connector);
    ~mixer_window();

    void on_updated_selection(dv_full_display_widget::SelectionType sel_type);

private:
    void cancel_effect();
    void begin_pic_in_pic();
    void begin_fade();
    void apply_effect();
    void open_format_dialog();
    void open_sources_dialog();

    void toggle_record() throw();
    bool update(Glib::IOCondition) throw();

    void set_pri_video_source(mixer::source_id);
    void set_sec_video_source(mixer::source_id);
    void switch_pri_sec_video_sources();

    virtual void put_frames(unsigned source_count,
			    const dv_frame_ptr * source_dv,
			    mixer::mix_settings,
			    const dv_frame_ptr & mixed_dv,
			    const raw_frame_ptr & mixed_raw);
    virtual void effect_status(int min, int cur, int max, bool more);

    mixer & mixer_;
    connector & connector_;

    Gtk::VBox main_box_;

    Gtk::MenuBar menu_bar_;
    Gtk::MenuItem file_menu_item_;
    Gtk::Menu file_menu_;
    Gtk::ImageMenuItem quit_menu_item_;
    Gtk::MenuItem settings_menu_item_;
    Gtk::Menu settings_menu_;
    Gtk::MenuItem format_menu_item_;
    Gtk::MenuItem sources_menu_item_;
    Gtk::HBox upper_box_;
    Gtk::VBox command_box_;
    Gtk::ToggleButton record_button_;
    Gtk::Button cut_button_;
    Gtk::HSeparator command_sep_;
    Gtk::RadioButtonGroup effect_group_;
    Gtk::RadioButton none_button_;
    Gtk::RadioButton pip_button_;
    Gtk::RadioButton fade_button_;
    Gtk::HScale fade_value_;
    Gtk::Button apply_button_;
    Gtk::ProgressBar progress_;
    Gtk::Button switch_a_b_button_;
    Gtk::RadioButtonGroup selection_group_;
    Gtk::VBox pip_box_;
    Gtk::HBox pip_selection_upper_box_;
    Gtk::Label pip_label_;
    Gtk::RadioButton set_selection_manual_button_;
    Gtk::HBox pip_selection_lower_box_;
    Gtk::RadioButton set_selection_nw_button_;
    Gtk::RadioButton set_selection_ne_button_;
    Gtk::RadioButton set_selection_se_button_;
    Gtk::RadioButton set_selection_sw_button_;
    Gtk::RadioButton set_selection_center_button_;
    Gtk::RadioButton set_selection_dummy_button_;
    Gtk::HSeparator meter_sep_;
    vu_meter vu_meter_;
    status_overlay osd_;
    dv_full_display_widget display_;
    dv_selector_widget selector_;

    mixer::source_id pri_video_source_id_, sec_video_source_id_;
    bool pip_active_;
    bool pip_pending_;
    bool fade_pending_;
    bool progress_active_;
    double progress_val_;
    mixer::source_id fade_target_;

    auto_pipe wakeup_pipe_;

    boost::mutex frame_mutex_; // controls access to the following
    std::vector<dv_frame_ptr> source_dv_;
    mixer::source_id next_source_id_;
    mixer::mix_settings mix_settings_;
    dv_frame_ptr mixed_dv_;
    raw_frame_ptr mixed_raw_;
};

#endif // !defined(DVSWITCH_MIXER_WINDOW_HPP)
