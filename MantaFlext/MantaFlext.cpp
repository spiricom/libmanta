#include "MantaFlext.h"

FLEXT_NEW("manta",manta)

manta::manta():
   shouldStop(false),
   running(false)
{ 
	AddInAnything();
	AddInAnything();

	AddOutAnything("Pad Velocity");
	AddOutAnything("Pad and Button Continuous");
	AddOutAnything("Slider");
	AddOutAnything("Processed");

   FLEXT_ADDMETHOD_2(1, "pad", SetPadLED, t_symptr, int);
   FLEXT_ADDMETHOD_3(1, "row", SetPadLEDRow, t_symptr, int, int);
   FLEXT_ADDMETHOD_3(1, "column", SetPadLEDColumn, t_symptr, int, int);
   FLEXT_ADDMETHOD_3(1, "slider", SetSliderLED, t_symptr, int, int);
   FLEXT_ADDMETHOD_2(1, "button", SetButtonLED, t_symptr, int);
   FLEXT_ADDMETHOD_2(0, "ledcontrol", SetLEDControl, t_symptr, int);
   /* use flext to call the threaded method */
   FLEXT_CALLMETHOD(StartThread);
} 

manta::~manta()
{ 
   shouldStop = true;
   while(running)
   {
      cond.Wait();
   }
   shouldStop = false;
} 

void manta::ClassSetup(t_classid c)
{
   padSymbol = MakeSymbol("pad");
   sliderSymbol = MakeSymbol("slider");
   buttonSymbol = MakeSymbol("button");
   amberSymbol = MakeSymbol("amber");
   offSymbol = MakeSymbol("off");
   redSymbol = MakeSymbol("red");
   rowSymbol = MakeSymbol("row");
   columnSymbol = MakeSymbol("column");
   frameSymbol = MakeSymbol("frame");
   padAndButtonSymbol = MakeSymbol("padandbutton");
}

const t_symbol *manta::padSymbol;
const t_symbol *manta::buttonSymbol;
const t_symbol *manta::sliderSymbol;
const t_symbol *manta::amberSymbol;
const t_symbol *manta::redSymbol;
const t_symbol *manta::offSymbol;
const t_symbol *manta::rowSymbol;
const t_symbol *manta::columnSymbol;
const t_symbol *manta::frameSymbol;
const t_symbol *manta::padAndButtonSymbol;
