/*************************************
 * Project:  BulbTempCalc            *
 * Purpose:  Calculates wet-bulb     *
 *           temperatures            *
 * File:     bulbtempcalc.c          *
 * Version:  1.0 RELEASE             *
 * Author:   Michael Bergmann        *
 * Date:     2026/25/06              *
 * Tested Compilers:                 *
 *         : SAS/C v6.58             *
 *           VBCC v0.91 pre          *
 *           amiga-gcc v6.5          *
 * HINT: Should be linked against    *
 *       amiga.lib and some math lib *
 ************************************
 */
#include <clib/macros.h>
#include <clib/alib_protos.h>
#include <clib/compiler-specific.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/utility.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/gadtools.h>
#include <proto/icon.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <proto/window.h>
#include <proto/layout.h>
#include <proto/integer.h>
#include <proto/string.h>
#include <proto/label.h>
#include <proto/requester.h>
#include <classes/requester.h>

#include <libraries/gadtools.h>
#include <reaction/reaction.h>
#include <intuition/gadgetclass.h>
#include <intuition/icclass.h>
#include <reaction/reaction_macros.h>
#include <classes/window.h>
#include <exec/memory.h>

#define mydebug FALSE  /* Debugging Texts TRUE or FALSE */

#define PROGRAMNAME     "BulbTempCalc"
#define VERSION         "1"
#define SUBVERSION      "0"
#define REVISION        "0"

/* construct version tag */
#if defined(__VBCC__)
  const UBYTE VersionTag[] = "$VER: " PROGRAMNAME " v" VERSION "." SUBVERSION "." REVISION " " __AMIGADATE__ "\n\0";
#endif
#if defined(__SASC)
  const UBYTE VersionTag[] = "$VER: " PROGRAMNAME " v" VERSION "." SUBVERSION "." REVISION " " __AMIGADATE__ "\n\0";
#endif

/* --- Function Proto Types ------------------ */
int req_about(Object *reactionWindow);
int req_info(Object *reactionWindow);
int req_warning(Object *reactionWindow);
DOUBLE calculateWetBulb(DOUBLE T, DOUBLE RH);
int setup( void );
void cleanup(void);
int main( int argc, char **argv );
void window_main( void );
void runWindow( Object *window_object, int window_id, 
                struct Menu *menu_strip, struct Gadget *win_gadgets[] );
                
/* --- Menu IDs -------------------------------------------------------------- */
enum menus
{
	/* Menu "Projekt"  */
	MN_NEW, MN_ABOUT, MN_QUIT,
	/* Menu "Help" */
	MN_MANUAL
};

/* --- Some global variables ------------------------------------------------- */
struct Screen	*gScreen = NULL;
struct DrawInfo	*gDrawInfo = NULL;
APTR gVisinfo = NULL;
struct MsgPort	*gAppPort = NULL;

// Feuchtkugelberechnung:
double temperature = 22.0;    // in °C
double humidity = 5.0;        // in %
double wettemperature = 8.71; // in °C


/* -- Easy Request structures -- */
struct EasyStruct warnreq =
  {
    sizeof(struct EasyStruct),
    0,
    "Error - no ReAction classes found on this Amiga system",
    "BulbTempCalc needs AmigaOS 3.2.x in order to run.\nI will quit now.",
    "Ok"
  };

int req_about(Object *reactionWindow)
{
  Object *reqobj;
  ULONG win;
  int res=0;

  GetAttr(WINDOW_Window, reactionWindow, &win);
  reqobj = NewObject(REQUESTER_GetClass(), NULL, REQ_Type, REQTYPE_INFO, REQ_Image, REQIMAGE_INFO,
       REQ_TitleText, "About BulbTempCalc",
       REQ_BodyText," BulbTempCalc v1.0\n\n Written by Micha B. 2026/06",
       REQ_GadgetText, "_OK",
       TAG_DONE);
  if (reqobj)
  {
    res=DoMethod(reqobj, RM_OPENREQ, NULL, win, NULL);
    DisposeObject(reqobj);
  }
  return res;
}

int req_info(Object *reactionWindow)
{
  Object *reqobj;
  ULONG win;
  int res=0;

  GetAttr(WINDOW_Window, reactionWindow, &win);
  reqobj = NewObject(REQUESTER_GetClass(), NULL, REQ_Type, REQTYPE_INFO, REQ_Image, REQIMAGE_DEFAULT,
       REQ_TitleText, "BulbTempCalc Help",
       REQ_BodyText," What is WetBulb Temperature all about?\n\n Wet-bulb temperature is the lowest temperature air can reach through evaporative cooling alone.\n It measures how effectively human sweat can cool the body. When it nears the human body's core\n temperature, the body loses its ability to cool itself, making it a critical indicator of heat stress and\n survivability\n" \
                    "Wet-bulb temperature is the lowest temperature air can reach through evaporative cooling alone.\n It measures how effectively human sweat can cool the body.\n\n When it nears the human body's core temperature, the body loses its ability to cool itself,\n making it a critical indicator of heat stress and survivability." \
                    "\n\n35°C (95°F): The recognized survivability limit. At this wet-bulb temperature, the air is so hot and humid\n that the human body can no longer cool itself, leading to heatstroke or death within hours.",
       REQ_GadgetText, "_OK",
       TAG_DONE);
  if (reqobj)
  {
    res=DoMethod(reqobj, RM_OPENREQ, NULL, win, NULL);
    DisposeObject(reqobj);
  }
  return res;
}

int req_warning(Object *reactionWindow)
{
  Object *reqobj;
  ULONG win;
  int res=0;

  GetAttr(WINDOW_Window, reactionWindow, &win);
  reqobj = NewObject(REQUESTER_GetClass(), NULL, REQ_Type, REQTYPE_INFO, REQ_Image, REQIMAGE_WARNING,
       REQ_TitleText, "BulpTempCalc Warning",
       REQ_BodyText," Your health is at risk.\n\n If the wet-bulb temperature reaches 35°C or above, there is an\n acute risk to life within 6 hours at the latest!!\n\n Higher temperatures will shorten this time frame.",
       REQ_GadgetText, "_OK",
       TAG_DONE);
  if (reqobj)
  {
    res=DoMethod(reqobj, RM_OPENREQ, NULL, win, NULL);
    DisposeObject(reqobj);
  }
  return res;
}

struct Library *WindowBase = NULL,
               *IntegerBase = NULL,
               *StringBase = NULL,
               *LabelBase = NULL,
               *RequesterBase = NULL,
               *GadToolsBase = NULL,
               *LayoutBase = NULL,
               *IconBase = NULL;
struct IntuitionBase *IntuitionBase = NULL;


//window ids
enum win { window_main_id = 4 };

//Window_Main gadgets
enum window_main_idx { vert_outer, vert_boxtemp, horiz_templine, int_temp, lbl_temp, 
  horiz_wetline, int_humidity, lbl_wet, vert_boxresult, horiz_outline, 
  str_result, lbl_result };
enum window_main_id { vert_outer_id = 6, vert_boxtemp_id = 7, horiz_templine_id = 8, 
  int_temp_id = 12, lbl_temp_id = 13, horiz_wetline_id = 10, int_humidity_id = 16, 
  lbl_wet_id = 17, vert_boxresult_id = 25, horiz_outline_id = 26, 
  str_result_id = 28, lbl_result_id = 29 };
  
int setup( void )
{
  if( !(IntuitionBase = (struct IntuitionBase*) OpenLibrary("intuition.library",0L)) ) return 0;
  if( !(GadToolsBase = (struct Library*) OpenLibrary("gadtools.library",0L) ) ) return 0;
  if( !(WindowBase = (struct Library*) OpenLibrary("window.class",0L) ) ) return 0;
  if( !(IconBase = (struct Library*) OpenLibrary("icon.library",0L) ) ) return 0;  
  if( !(LayoutBase = (struct Library*) OpenLibrary("gadgets/layout.gadget",47L) ) )
  {
    EasyRequest(NULL, &warnreq, NULL);
    return 0;
  }
  if( !(IntegerBase = (struct Library*) OpenLibrary("gadgets/integer.gadget",0L) ) ) return 0;
  if( !(StringBase = (struct Library*) OpenLibrary("gadgets/string.gadget",0L) ) ) return 0;
  if( !(LabelBase = (struct Library*) OpenLibrary("images/label.image",0L) ) ) return 0;
  if( !(RequesterBase = (struct Library*) OpenLibrary("requester.class",0L) ) ) return 0;
  if( !(gScreen = LockPubScreen( 0 ) ) ) return 0;
  if( !(gVisinfo = GetVisualInfo( gScreen, TAG_DONE ) ) ) return 0;
  if( !(gDrawInfo = GetScreenDrawInfo ( gScreen ) ) ) return 0;
  if( !(gAppPort = CreateMsgPort() ) ) return 0;

  return -1;
}

void cleanup( void )
{
  if ( gDrawInfo ) FreeScreenDrawInfo( gScreen, gDrawInfo);
  if ( gVisinfo ) FreeVisualInfo( gVisinfo );
  if ( gAppPort ) DeleteMsgPort( gAppPort );
  if ( gScreen ) UnlockPubScreen( 0, gScreen );

  if (GadToolsBase) CloseLibrary( (struct Library *)GadToolsBase );
  if (IconBase) CloseLibrary( (struct Library *)IconBase );
  if (IntuitionBase) CloseLibrary( (struct Library *)IntuitionBase );
  if (IntegerBase) CloseLibrary( (struct Library *)IntegerBase );
  if (StringBase) CloseLibrary( (struct Library *)StringBase );
  if (LabelBase) CloseLibrary( (struct Library *)LabelBase );
  if (LayoutBase) CloseLibrary( (struct Library *)LayoutBase );
  if (WindowBase) CloseLibrary( (struct Library *)WindowBase );
  if (RequesterBase) CloseLibrary( (struct Library *)RequesterBase );
}

void runWindow( Object *window_object, int window_id, struct Menu *menu_strip, struct Gadget *win_gadgets[] )
{
  struct Window	*main_window = NULL;
  struct MenuItem *menuitem = NULL;
	LONG myItem = 0;
	int req_result = 0;
	ULONG myTemp = 0, myHum = 0;
	char buffer[20];
	
  if ( window_object )
  {
    if ( main_window = (struct Window *) RA_OpenWindow( window_object ))
    {
      WORD Code;
      ULONG wait = 0, signal = 0, result = 0, done = FALSE;
      GetAttr( WINDOW_SigMask, window_object, &signal );
      
      if ( menu_strip)  SetMenuStrip( main_window, menu_strip );
      while ( !done)
      {
        wait = Wait( signal | SIGBREAKF_CTRL_C );

        if ( wait & SIGBREAKF_CTRL_C )
          done = TRUE;
        else
          while (( result = RA_HandleInput( window_object, &Code )) != WMHI_LASTMSG)
          {
            switch ( result & WMHI_CLASSMASK )
            {
              case WMHI_CLOSEWINDOW:
                done = TRUE;
                break;

              case WMHI_MENUPICK:
                menuitem = ItemAddress(menu_strip, result & WMHI_MENUMASK);
								if(mydebug)
								{
									puts("menu pick");
									printf("ItemAdress = %ld\n", menuitem);
								}
								
								/* Check if menuitem equals to Zero. If Zero, an enforcer hit will occour when */
								/* attempting to examine,so we do not allow switching on menuitem == 0!        */
								if(!(menuitem == 0))
								{
  								 /* --- ...get menu entries by using GadTools' GTMENUITEM_USERDATA field macro --- */                 
									myItem = ((long)GTMENUITEM_USERDATA(ItemAddress(menu_strip, result & WMHI_MENUMASK)));
									/* --- Identify selected menu entry      */ 
									switch(myItem)
									{
  									/* --- Menu "Project" --- */
										case MN_NEW:
  										SetGadgetAttrs( win_gadgets[int_temp], main_window, NULL, INTEGER_Number, 22, TAG_END );
  										SetGadgetAttrs( win_gadgets[int_humidity], main_window, NULL, INTEGER_Number, 5, TAG_END );
  										SetGadgetAttrs( win_gadgets[str_result], main_window, NULL, STRINGA_TextVal, "6.71", TAG_END );
  										
											if(mydebug)
											{
												puts("NEW");
											}  										
											break;
										case MN_ABOUT:
											if(mydebug)
											{
												puts("ABOUT");
											}
											SetAttrs(window_object, WA_BusyPointer, TRUE, TAG_DONE);  /* Modal: ON */
											req_result = req_about(window_object);
											SetAttrs(window_object, WA_BusyPointer, FALSE, TAG_DONE); /* Modal: OFF */
											break;
										case MN_QUIT:
											if(mydebug)
											{
												puts("QUIT");
											}
											done = TRUE;
											break;
										case MN_MANUAL:
											if(mydebug)
											{
												puts("HELP");
											}
											SetAttrs(window_object, WA_BusyPointer, TRUE, TAG_DONE);  /* Modal: ON */
											/* call Info-Requester */
											req_info(window_object);
											SetAttrs(window_object, WA_BusyPointer, FALSE, TAG_DONE); /* Modal: OFF */
											break;
									} // END switch(myItem)
								} // END if(!(menuitem == 0))
                break;

              case WMHI_GADGETUP:
              if(mydebug)
                 puts("gadget press");
              switch (result & WMHI_GADGETMASK)
								{
    							case int_temp_id:
    								// Get Humidity value
      							GetAttr(INTEGER_Number, (Object *)win_gadgets[int_temp], &myTemp);
      							temperature = (double)myTemp;
      							wettemperature = calculateWetBulb(temperature, humidity);
      							// convert Double to String:
                    sprintf(buffer, "%.2f", wettemperature);
      							// Set result
                    SetGadgetAttrs( win_gadgets[str_result], main_window, NULL, STRINGA_TextVal, buffer, TAG_END );
                    if(wettemperature >= 35.00)
                    {
                      SetAttrs(window_object, WA_BusyPointer, TRUE, TAG_DONE);  /* Modal: ON */
											req_result = req_warning(window_object); 
											SetAttrs(window_object, WA_BusyPointer, FALSE, TAG_DONE); /* Modal: OFF */ 
                    }
                    
    								if(mydebug)
    								{
      								puts("Temperature changed.");
      								printf("Temperature: %2.2f\n", temperature);
      								printf("Humidity: %2.2f\n", humidity);
      								printf("Wet-Temp: %2.2f\n", wettemperature);
      								printf("Temp-String: %s\n", buffer);
    								}
    								break;
    							case int_humidity_id:
      							// Get Humidity value
      							GetAttr(INTEGER_Number, (Object *)win_gadgets[int_humidity], &myHum);
      							humidity = (double)myHum;
      							wettemperature = calculateWetBulb(temperature, humidity);
      							sprintf(buffer, "%.2f", wettemperature);
                    SetGadgetAttrs( win_gadgets[str_result], main_window, NULL, STRINGA_TextVal, buffer, TAG_END );
                    if(wettemperature >= 35.00)
                    {
                      SetAttrs(window_object, WA_BusyPointer, TRUE, TAG_DONE);  /* Modal: ON */
											req_result = req_warning(window_object); 
											SetAttrs(window_object, WA_BusyPointer, FALSE, TAG_DONE); /* Modal: OFF */ 
                    }
                    
    								if(mydebug)
    								{
      								puts("Humidity changed.");
      								printf("Temperature: %2.2f\n", temperature);      								
      								printf("Humidity: %2.2f\n", humidity);
      								printf("Wet-Temp: %2.2f\n", wettemperature);
    								}
    								break;
								} // END switch (result & WMHI_GADGETMASK)               
                break;

              case WMHI_ICONIFY:
                if ( RA_Iconify( window_object ) )
                  main_window = NULL;
                break;

              case WMHI_UNICONIFY:
                main_window = RA_OpenWindow( window_object );
                if ( menu_strip)  SetMenuStrip( main_window, menu_strip );
              break;

            }
          }
      }
    }
  }
}

void window_main( void )
{
  struct NewMenu menuData[] =
  {
    { NM_TITLE, "Project", 0, 0, 0, NULL },
    { NM_ITEM, "New...", "N", 0, 30, (APTR)MN_NEW },
    { NM_ITEM, NM_BARLABEL, 0, 0, 29, NULL },
    { NM_ITEM, "About...", "?", 0, 27, (APTR)MN_ABOUT },
    { NM_ITEM, NM_BARLABEL, 0, 0, 23, NULL },
    { NM_ITEM, "Quit", "Q", 0, 15, (APTR)MN_QUIT },
    { NM_TITLE, "Help", 0, 0, 0, NULL },
    { NM_ITEM, "What is 'Wet Bulb Temperature'?", "H", 0, 0, (APTR)MN_MANUAL },
    { NM_END, NULL, 0, 0, 0, (APTR)0 }
  };

  struct Menu	*menu_strip = NULL;
  struct Gadget	*main_gadgets[ 13 ];
  Object *window_object = NULL;
  struct HintInfo hintInfo[] =
  {
    {vert_outer_id,-1,"",0},
    {vert_boxtemp_id,-1,"",0},
    {horiz_templine_id,-1,"",0},
    {int_temp_id,-1,"Input: Temperature in °C",0},
    {lbl_temp_id,-1,"",0},
    {horiz_wetline_id,-1,"",0},
    {int_humidity_id,-1,"Input: Humidity in %",0},
    {lbl_wet_id,-1,"",0},
    {vert_boxresult_id,-1,"",0},
    {horiz_templine_id,-1,"",0},
    {str_result_id,-1,"Output: resulting wet bulb temperature",0},
    {lbl_temp_id,-1,"",0},
    {-1,-1,NULL,0}
  };
  menu_strip = CreateMenusA( menuData, TAG_END );
  LayoutMenus( menu_strip, gVisinfo,
    GTMN_NewLookMenus, TRUE,
    TAG_DONE );


  window_object = NewObject( WINDOW_GetClass(), NULL, 
    WA_Title, "BulbTempCalc",
    WA_ScreenTitle, "BulbTempCalc v1.0 (c) 2026 by Micha B. / MB-SoftWorX",
    WA_Left, 5,
    WA_Top, 20,
    WA_Width, 250,
    WA_Height, 20,
    WA_MinWidth, 250,
    WA_MinHeight, 20,
    WA_MaxWidth, 8192,
    WA_MaxHeight, 8192,
    WINDOW_LockHeight, TRUE,
    WINDOW_IconifyGadget, TRUE,
    WINDOW_HintInfo, hintInfo,
    WINDOW_GadgetHelp, TRUE,
    WINDOW_AppPort, gAppPort,
    WINDOW_IconifyGadget, TRUE,
    WA_CloseGadget, TRUE,
    WA_DepthGadget, TRUE,
    WA_SizeGadget, TRUE,
    WA_DragBar, TRUE,
    WA_Activate, TRUE,
    WA_SizeBBottom, TRUE,
    WINDOW_Position, WPOS_TOPLEFT,
    WINDOW_IconTitle, "BulbTempCalc",
    WINDOW_Icon,  GetDiskObject("BulbTempCalc"),
    WA_NoCareRefresh, TRUE,
    WA_IDCMP, IDCMP_GADGETDOWN | IDCMP_GADGETUP | IDCMP_CLOSEWINDOW | IDCMP_MENUPICK | IDCMP_NEWSIZE | IDCMP_VANILLAKEY | IDCMP_IDCMPUPDATE,
    WINDOW_ParentGroup, NewObject( LAYOUT_GetClass(), NULL,
    LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
    LAYOUT_SpaceOuter, TRUE,
    LAYOUT_DeferLayout, TRUE,
      LAYOUT_AddChild, main_gadgets[vert_outer] = NewObject( LAYOUT_GetClass(), NULL, 
        GA_ID, vert_outer_id,
        LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
        LAYOUT_AddChild, main_gadgets[vert_boxtemp] = NewObject( LAYOUT_GetClass(), NULL, 
          GA_ID, vert_boxtemp_id,
          LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
          LAYOUT_BevelStyle, BVS_THIN,
          LAYOUT_SpaceOuter, TRUE,
          LAYOUT_LeftSpacing, 2,
          LAYOUT_RightSpacing, 2,
          LAYOUT_TopSpacing, 2,
          LAYOUT_BottomSpacing, 2,
          LAYOUT_Label, "Parameters",
          LAYOUT_DeferLayout, TRUE,
          LAYOUT_AddChild, main_gadgets[horiz_templine] = NewObject( LAYOUT_GetClass(), NULL, 
            GA_ID, horiz_templine_id,
            LAYOUT_Orientation, LAYOUT_ORIENT_HORIZ,
            LAYOUT_SpaceOuter, TRUE,
            LAYOUT_DeferLayout, TRUE,
            LAYOUT_AddChild, main_gadgets[int_temp] = NewObject( INTEGER_GetClass(), NULL, 
              GA_ID, int_temp_id,
              GA_RelVerify, TRUE,
              GA_TabCycle, TRUE,
              INTEGER_Minimum, -20,
              INTEGER_Maximum, 50,
              INTEGER_MinVisible, 3,
              INTEGER_Number, 22,
            TAG_END),
            CHILD_Label, NewObject( LABEL_GetClass(), NULL, 
              LABEL_Text, "Temperature (T):",
            TAG_END),
            LAYOUT_AddImage, main_gadgets[lbl_temp] = NewObject( LABEL_GetClass(), NULL, 
              GA_ID, lbl_temp_id,
              LABEL_DrawInfo, gDrawInfo,
              LABEL_Text, "°C",
            TAG_END),
          TAG_END),
          LAYOUT_AddChild, main_gadgets[horiz_wetline] = NewObject( LAYOUT_GetClass(), NULL, 
            GA_ID, horiz_wetline_id,
            LAYOUT_Orientation, LAYOUT_ORIENT_HORIZ,
            LAYOUT_SpaceOuter, TRUE,
            LAYOUT_DeferLayout, TRUE,
            LAYOUT_AddChild, main_gadgets[int_humidity] = NewObject( INTEGER_GetClass(), NULL, 
              GA_ID, int_humidity_id,
              GA_RelVerify, TRUE,
              GA_TabCycle, TRUE,
              INTEGER_Minimum, 5,
              INTEGER_Maximum, 99,
              INTEGER_MinVisible, 2,
            TAG_END),
            CHILD_Label, NewObject( LABEL_GetClass(), NULL, 
              LABEL_Text, "Humidity:       (H):",
            TAG_END),
            LAYOUT_AddImage, main_gadgets[lbl_wet] = NewObject( LABEL_GetClass(), NULL, 
              GA_ID, lbl_wet_id,
              LABEL_DrawInfo, gDrawInfo,
              LABEL_Text, "%",
            TAG_END),
          TAG_END),
        TAG_END),
        LAYOUT_AddChild, main_gadgets[vert_boxresult] = NewObject( LAYOUT_GetClass(), NULL, 
          GA_ID, vert_boxresult_id,
          LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
          LAYOUT_BevelStyle, BVS_THIN,
          LAYOUT_SpaceOuter, TRUE,
          LAYOUT_LeftSpacing, 2,
          LAYOUT_RightSpacing, 2,
          LAYOUT_TopSpacing, 2,
          LAYOUT_BottomSpacing, 2,
          LAYOUT_Label, "Result",
          LAYOUT_DeferLayout, TRUE,
          LAYOUT_AddChild, main_gadgets[horiz_templine] = NewObject( LAYOUT_GetClass(), NULL, 
            GA_ID, horiz_templine_id,
            LAYOUT_Orientation, LAYOUT_ORIENT_HORIZ,
            LAYOUT_SpaceOuter, TRUE,
            LAYOUT_DeferLayout, TRUE,
            LAYOUT_AddChild, main_gadgets[str_result] = NewObject( STRING_GetClass(), NULL, 
              GA_ID, str_result_id,
              GA_RelVerify, TRUE,
              GA_TabCycle, TRUE,
              GA_ReadOnly, TRUE,
              STRINGA_TextVal, "6.71",
              STRINGA_MaxChars, 10,
              STRINGA_Justification, GACT_STRINGCENTER,
            TAG_END),
            CHILD_Label, NewObject( LABEL_GetClass(), NULL, 
              LABEL_Text, "WetBulbTemp (Tw):",
            TAG_END),
            LAYOUT_AddImage, main_gadgets[lbl_temp] = NewObject( LABEL_GetClass(), NULL, 
              GA_ID, lbl_temp_id,
              LABEL_DrawInfo, gDrawInfo,
              LABEL_Text, "°C",
            TAG_END),
          TAG_END),
        TAG_END),
      TAG_END),
    TAG_END),
  TAG_END);  
  main_gadgets[12] = 0;

  runWindow( window_object, window_main_id, menu_strip, main_gadgets );

  if ( window_object ) DisposeObject( window_object );
  if ( menu_strip ) FreeMenus( menu_strip );
}

int main( int argc, char **argv )
{
  if ( setup() )
  {
    window_main();
  }
  cleanup();
}

/* ------ Temperaturberechnung ---------------------- */
// Funktion zur Berechnung der Feuchtkugeltemperatur (Wet Bulb Temperature)
DOUBLE calculateWetBulb(DOUBLE T, DOUBLE RH)
{
    // Näherungsformel nach Stull
    double T_w = T * atan(0.151977 * sqrt(RH + 8.313659)) +
                 atan(T + RH) -
                 atan(RH - 1.676331) +
                 0.00391838 * pow(RH, 1.5) * atan(0.023101 * RH) -
                 4.686035;

    return T_w;
}
