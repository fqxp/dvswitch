// Copyright 2009 Ben Hutchings.
// See the file "COPYING" for licence details.

#ifndef DVSWITCH_STATUS_OVERLAY_HPP
#define DVSWITCH_STATUS_OVERLAY_HPP

#include <gtkmm/container.h>
#include <gtkmm/drawingarea.h>

class status_overlay : public Gtk::Container
{
public:
    status_overlay();
    ~status_overlay();
    void set_status(const Glib::ustring & text,
		    const Glib::ustring & icon_name,
		    unsigned timeout = 0);

private:
    virtual GType child_type_vfunc() const;
    virtual void forall_vfunc(gboolean include_internals,
			      GtkCallback callback,
			      gpointer callback_data);
    virtual void on_add(Gtk::Widget * widget);
    virtual void on_remove(Gtk::Widget * widget);
    virtual void on_size_allocate(Gtk::Allocation & allocation);
    virtual void on_size_request(Gtk::Requisition *);

    bool clear();

    class status_widget : public Gtk::DrawingArea
    {
    public:
	void set_status(const Glib::ustring & text,
			const Glib::ustring & icon_name);

    private:
	virtual bool on_expose_event(GdkEventExpose *) throw();

	Glib::ustring text_;
	Glib::RefPtr<Gdk::Pixbuf> icon_;
    };

    Gtk::Widget * main_widget_;
    status_widget status_widget_;
    Glib::RefPtr<Glib::TimeoutSource> timer_;
};

#endif // DVSWITCH_STATUS_OVERLAY_HPP
