#include <vgGTK/event/sdl.hpp>

#include <vgSDL/event/EventHandler.hpp>
#include <gtkmm.h>


namespace vgGTK
{
namespace event
{


namespace {


gboolean my_source_prepare  (GSource    *source,
							 gint       *timeout_)
{
	 return false;
}

gboolean my_source_check    (GSource    *source)
{
	return vgSDL::event::EventHandler::getEvents();
}

gboolean my_source_dispatch (GSource    *source,
			GSourceFunc callback,
			gpointer    user_data)
{
	vgSDL::event::EventHandler::dispatchEvents();
	return true;
}

}


void initSDL()
{

	vgSDL::event::EventHandler::getEvents();
	GSourceFuncs* source=new GSourceFuncs;
	source->prepare=&my_source_prepare;
	source->check=&my_source_check;
	source->dispatch=&my_source_dispatch;
	source->finalize=0;
	GSource* gs = g_source_new(source, sizeof(GSource));
	g_source_attach(gs,0);
}

} // namespace event
} // namespace vgGTK
