// ----------------------------------------------------------------------------
// Datei :	BarBarn.cpp
// Zweck :	Methoden der Klasse BarBarn
// ----------------------------------------------------------------------------
//
// Erfordert Win2000, XP, Vista, Win95, Win98, WinNT
// ----------------------------------------------------------------------------

#include "BarBarn.h"
#include <iostream>
#include <string>
#include <sstream>		// für die Umwandlung float -> string

using namespace std;

#define MAX_TEXT_LENGTH		30
#define LENGTH_OVERFLOW_TEXT		"*******Caption zu lang********"	// darf max die Laenge von MAX_TEXT_LENGTH haben
#define LENGTH						50			// maximale Länge der Bar

///////////////////////////////////////////////////////////
// Konstruktor von Bar
Bar::Bar(	unsigned int line, unsigned int maxVal, unsigned int state,
					string caption, char sign, bool right,
					bool inColor, int color, bool visible)
{
	// Kleinscheiss
	this->line		= line;
	this->maxVal	= maxVal;
	this->inColor	= inColor;
	this->right		= right;
	this->visible	= visible;
	this->sign		= sign;
	//	this->col	= col;

	// Caption initialisieren
	if( caption.length() > MAX_TEXT_LENGTH)
		this->caption = LENGTH_OVERFLOW_TEXT;
	else
	{
		string whitespace( 30-caption.length(), ' ');
		this->caption= caption+whitespace;
	}

	// State initialisieren
	if( state <= maxVal)
		this->state = state;
	else
		this->state = maxVal;

	if( visible)
		draw();
}

///////////////////////////////////////////////////////////
// draw-Methode
char Bar::draw()
{
	// aktuelle Cursorposition sichern
	int actLine;
	int actRow;
	getCursorPos( actLine, actRow);

	// Anzahl der zu fuellenden Kaestchen
	char bloques = char( (float)state/(float)maxVal * LENGTH);

	if(visible)
	{
		// springe mit Cursor an angegebene Line
		cursorOff();
		setCursor( line, 0);
		// Zeile löschen
		string leerline( 80, ' ');
		cout << leerline;
		setCursor( line, 0);

		// Prozentleiste
		string leiste( (int)bloques, sign);
		// leerer Teil der Leiste
		string leer( (LENGTH - bloques), ' ');

		int l2lngth = 80 - bloques - leer.length() - caption.length();
		string leer2( l2lngth, ' ');
		if( !right)
			cout << caption << leer << leiste;
		else
			cout << leiste  << leer << caption << leer2;
	}

	// Cursor zurücksetzen
	cursorOn();
	setCursor( actLine, actRow);

	return bloques;
}

///////////////////////////////////////////////////////////
// drawWithPercentCaption-Methode
// (char bildet das Trennzeichen)
char Bar::drawWithPercentCaption( unsigned int state, char delimeter, string caption)
{
	setState( state);
	setCaption( delimeter + percentAsString() + "% " + caption);
	return draw();
}

///////////////////////////////////////////////////////////
// drawWithStateCaption-Methode
// (char bildet das Trennzeichen)
char Bar::drawWithStateCaption( unsigned int state, char delimeter, string caption)
{
	setState( state);

	std::ostringstream StringHelper;
	StringHelper << this->state;
	std::ostringstream StringHelper2;
	StringHelper2 << this->maxVal;

	caption = delimeter + StringHelper.str() + '/' + StringHelper2.str() + ' ' + caption;
	setCaption( caption);

	return draw();
}
///////////////////////////////////////////////////////////
// Bar::setup
void Bar::setup( unsigned int line, unsigned int maxVak, unsigned int state,
								string caption, char sign, bool right, bool inColor, int color, bool visible)
{
	// Kleinscheiss
	this->line		= line;
	this->maxVal	= maxVal;
	this->inColor	= inColor;
	this->right		= right;
	this->visible	= visible;
	this->sign		= sign;
	//	this->col			= col;


	// Caption initialisieren
	if( caption.length() > MAX_TEXT_LENGTH)
		this->caption = LENGTH_OVERFLOW_TEXT;
	else
	{
		string whitespace( 30-caption.length(), ' ');
		this->caption= caption + whitespace;
	}

	// State initialisieren
	if( state <= maxVal)
		this->state = state;
	else
		this->state = maxVal;
}

///////////////////////////////////////////////////////////
// Bar::percent gibt Prozentverhaeltnis
// state/maxVal zurueck
float Bar::percent()
{	return 100.0 * (double)state / (float)maxVal; }

///////////////////////////////////////////////////////////
// Bar::percentAsString()
string Bar::percentAsString()
{
		std::ostringstream floatStringHelper;
		floatStringHelper << percent();
    return floatStringHelper.str();
}

///////////////////////////////////////////////////////////
// Bar::changeLine drawt eine neue Line
char Bar::changeLine( unsigned int line, bool zeichnen, bool overwrite, char overwriteWith)
{
	// ggf alte Bar überschreiben
	if( overwrite)
	{
		// aktuelle Cursorposition sichern
		int actLine;
		int actRow;
		getCursorPos( actLine, actRow);

		string empty( 80, overwriteWith);
		cursorOff();
		setCursor( this->line, 0);
		cout << empty;

		setCursor( actLine, actRow);
	}

	this->line = line;

	if( zeichnen)
		return draw();
	return 'B';
}

///////////////////////////////////////////////////////////
// get-Methoden
char Bar::getSign()			// getSign
{ return sign;}

unsigned int Bar::getMaxVal()	// getMaxVal
{ return maxVal;}

unsigned int Bar::getState()	// getState
{ return state;}

unsigned int Bar::getLine()		// getLine
{ return line;}

string Bar::getCaption()		// getCaption
{ return caption;}

bool Bar::isCaptionRight()		// is Captionright
{ return right;}

bool Bar::isInColor()		// isInColor
{ return inColor; }

bool Bar::isVisible()		// isVisible
{ return visible;}

///////////////////////////////////////////////////////////
// set-Methoden
void Bar::setSign( char sign)								// setSign
{ this->sign		= sign; }

void Bar::setMaxVal( unsigned int maxVal)		// setMaxVal
{ this->maxVal	= maxVal; }

bool Bar::setState( unsigned int state)		// setState
{
	if( state <= maxVal)
	{
		this->state = state;
		return true;
	}
	else
	{
		this->state = maxVal;
		return false;
	}
}

void Bar::setLine( unsigned int line)		// setLine
{ this->line = line; }

bool Bar::setCaption( string caption)		// setCaption
{
	if( caption.length() > MAX_TEXT_LENGTH)
	{
		this->caption = LENGTH_OVERFLOW_TEXT;
		return false;
	}
	else
	{
		string whitespace( 30-caption.length(), ' ');
		this->caption= caption+whitespace;
		return true;
	}
}

void Bar::setCaptionRight( bool right)		// setCaptionRight
{ this->right		= right;}

void Bar::withColor( bool inColor)		// inColor
{ this->inColor	= inColor; }

void Bar::setVisibility( bool visible)		// setVisibility
{ this->visible	= visible; }
