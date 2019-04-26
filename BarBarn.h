// ----------------------------------------------------------------------------
// Datei :	BarBarn.h
// Zweck :	Klasse BarBarn zur Darstellung einer Prozentbar in der
//					Eingabeaufforderung
// ----------------------------------------------------------------------------
//
// Erfordert Win2000, XP, Vista, Win95, Win98, WinNT
//
// TODO: Die Farbeinstellungen müssen noch gemacht werden
// ----------------------------------------------------------------------------

#ifndef _BAR_BARN_
#define _BAR_BARN_

#include "consoleBarn.h"
#include <string>
using namespace std;

class Bar
{
	private:
		char lenght;					// eigentliche Länge der Bar
		char sign;						// Zeichen welches Prozentbalken darstellt
		unsigned int maxVal;	// max annehmbarer Wert
		unsigned int state;		// aktueller Wert
		unsigned int line;	// Zeile wo die Bar halt chillt
		string caption;				// die Caption halt
		bool right;						// Caption rechts?
		bool inColor;					// Farbe verwenden?
		bool visible;					// sichtBAR?
		// color col;					// späta...


	public:

		// Konstruktor
		Bar(	unsigned int line, unsigned int maxVal, unsigned int state,
					string caption, char sign, bool right,
					bool inColor, int color, bool visible);

		// draw-Funktion (gibt die Anzahl der gezeichneten Blöcke wieder)
		char draw();
		char drawWithPercentCaption( unsigned int state, char delimeter, string caption);
		char drawWithStateCaption( unsigned int state, char delimeter, string caption);

		// setUp Fun
		void setup(	unsigned int line, unsigned int maxVal, unsigned int state,
					string caption, char sign, bool right,
					bool inColor, int color, bool visible);

		// percent()
		float percent();
		string percentAsString();

		// changeLine Methode (drawt die line Gleich neu)
		char changeLine( unsigned int line, bool draw, bool overwrite = true, char overwriteWith=' ');

		//get-Methoden
		char getSign();
		unsigned int getMaxVal();
		unsigned int getState();
		unsigned int getLine();
		string getCaption();
		bool isCaptionRight();
		bool isInColor();
		bool isVisible();
		//color getColor();

		//set-Methoden
		void setSign( char sign);
		void setMaxVal( unsigned int maxVal);
		bool setState( unsigned int state);
		void setLine( unsigned int line);
		bool setCaption( string caption);
		void setCaptionRight( bool right);
		void withColor( bool inColor);
		void setVisibility( bool visible);
		//color setColor( color col);

};

#endif
