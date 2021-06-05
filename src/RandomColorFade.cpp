#include <RandomColorFade.h>


//executes the routine
//checks if the counter is ready an then sets a new color
void RandomColorFade::loop()
{
    if (this->ChangeColor.isTimerReady())
    {
        if (p_argb->canShow() == true)
        {
            this->ChangeColor.startTimer(random(10000, 60000));
            p_argb->changeColorWithTransition(p_argb->generateRandomColor(), FADE_TO);
        }
    }
}