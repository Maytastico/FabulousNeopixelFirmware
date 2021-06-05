#include "RandomColor.h"

void RandomColor::fillRandomFrame()
{
    for (unsigned int i = 0; i < _pcontroller->numPixels(); i++)
    {
        //sets a random color to every pixel
        uint32_t randomColor = _pcontroller->generateRandomColor();
        //Serial.println("Filling array on " + String(i) + " with " + String(randomColor));
        this->colors[i] = randomColor;
    }
}

void RandomColor::displayRandomFrame()
{
    //prepares the frame
    for (unsigned int i = 0; i < _pcontroller->numPixels(); i++)
    {
        _pcontroller->setPixelColor(i, this->colors[i]);
        //Serial.print("i :" + String(this->colors[i]) + " ; ");
    }
    //Serial.println("");
    //sends the pixel data to the stripe
    _pcontroller->show();
    //Serial.println("Executing Frame");
}

void RandomColor::colorStates()
{
    switch (states)
    {
    case SHOW_FIRST:
        //Waits until the Transition was finished
        if (_pcontroller->canShow())
        {
            this->displayRandomFrame();

            if (_pTransition->getCurrentTransitionState() == STDBY)
            {
                this->states = LOOP;
            }
        }
        break;
    case LOOP:
        if (_pcontroller->canShow())
        {
            uint8_t repeat = _pcontroller->numPixels() / random(1, 10);
            //Serial.println("Repeating: " + String(repeat));
            for (uint8_t i = 0; repeat >= i; i++)
            {
                uint32_t randomColor = _pcontroller->generateRandomColor();
                uint8_t randomPosition = _pcontroller->generateRadomPosition();
                //Serial.println("New color on " + String(randomPosition) + " : " + String(randomColor));
                this->colors[randomPosition] = randomColor;
                this->displayRandomFrame();
            }
            _pcontroller->show();
        }
        break;
    }
}

void RandomColor::resetStateMachine()
{
    this->states = SHOW_FIRST;
}

void RandomColor::loop()
{
    if(this->states ==SHOW_FIRST && static_cast<uint8_t>(_pTransition->getCurrentTransitionState())>2){
        this->colorStates();
    }else{
        if (cycle.isTimerReady())
        {
            cycle.startTimer(random(4000, 20000));
            this->colorStates();
        }
    }
}