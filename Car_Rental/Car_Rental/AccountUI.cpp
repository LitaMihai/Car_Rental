#include "AccountUI.h"

bool AccountUI::OnInit()
{
	AccountFrame* frame = new AccountFrame();
	frame->Show(true);
	return true;
}
