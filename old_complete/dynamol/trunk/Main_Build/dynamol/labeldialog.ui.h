/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


void labelDialog::customSlot( bool toggle )
{
   customEdit->setEnabled(toggle);
}

void labelDialog::clearSlot() {
   symbol->setChecked(false);
   type->setChecked(false);
   atomNum->setChecked(false);
   custom->setChecked(false);
   resName->setChecked(false);
   resNum->setChecked(false);
   charge->setChecked(false);
}


























