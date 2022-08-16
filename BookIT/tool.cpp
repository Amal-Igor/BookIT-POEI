#include "tool.h"

Tool::Tool()
{

}

int Tool::phoneNumber() const
{
    return mPhoneNumber;
}

void Tool::setPhoneNumber(int newPhoneNumber)
{
    mPhoneNumber = newPhoneNumber;
}
