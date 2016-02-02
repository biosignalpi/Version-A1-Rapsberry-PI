#ifndef SAVEASTEXT_H
#define SAVEASTEXT_H


#include "ecgstream.h"
#include "ecgstream_fourchannels.h"



/**
 * \function saveAsText
 * \brief The main model responsible for the logic of the MVC-part
 *
 * used by main
 * combines device with DataStream object
 * \author Martin
 * \bugs No known Bugs
 *
*/
struct A {

void saveAsText(EcgStream);
void saveAsText(EcgStream_four);

};
#endif // SAVEASTEXT_H
