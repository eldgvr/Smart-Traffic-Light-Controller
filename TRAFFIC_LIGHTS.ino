/*
  Smart Traffic Light Controller
  Team: CASCADE-X

  Hardware:
  Gaurav Singh Chandel

  Software:
  Anurag Kumar
*/
enum State
{
    RED,
    YELLOW_TO_GREEN,
    GREEN,
    YELLOW_TO_RED,
    PEDESTRIAN
};

// PIN DEFINITIONS

const int RED_LED = 8;
const int YELLOW_LED = 9;
const int GREEN_LED = 10;
const int BUZZER = 11;
const int BUTTON = 2;

// TRAFFIC LIGHT FUNCTIONS

void setRed()
{
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
}

void setYellow()
{
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
}

void setGreen()
{
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
}

void buzzerOff()
{
    digitalWrite(BUZZER, LOW);
}

// FSM VARIABLES

State currentState = RED; 

unsigned long previousMillis = 0;

// BUZZER VARIABLES

unsigned long buzzerMillis = 0;

bool buzzerState = false;

// PEDESTRIAN REQUEST

bool pedestrianRequest = false;

// BUTTON DEBOUNCE VARIABLES

unsigned long debounceMillis = 0;

bool currentButtonState = HIGH;
bool lastRawButtonState = HIGH;

bool stableButtonState = HIGH;
bool previousStableState = HIGH;

// BUTTON HANDLER

void handleButton(unsigned long currentMillis)
{
    currentButtonState = digitalRead(BUTTON);

    if (currentButtonState != lastRawButtonState)
    {
        debounceMillis = currentMillis;
    }

    // Check if button remained stable for 50 ms
    if (currentMillis - debounceMillis >= 50)
    {
        stableButtonState = currentButtonState;
    }

    // Detect one genuine button press
    if (stableButtonState == LOW &&
        previousStableState == HIGH)
    {
        if (currentState == GREEN)
        {
            pedestrianRequest = true;
        }
    }
    // Update button states
    previousStableState = stableButtonState;
    lastRawButtonState = currentButtonState;
}

    void setup()
    {
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    pinMode(BUZZER, OUTPUT);

    pinMode(BUTTON, INPUT_PULLUP);
    }

void loop()
{
    unsigned long currentMillis = millis();

    // Handle button and debounce
    handleButton(currentMillis);

    // TRAFFIC LIGHT FSM

    switch (currentState)
    {
        case RED:

            setRed();
            buzzerOff();

            if (pedestrianRequest)
            {
                currentState = PEDESTRIAN;

                previousMillis = currentMillis;

                // Reset buzzer
                buzzerMillis = currentMillis;
                buzzerState = false;

                buzzerOff();
            }

            else if (currentMillis - previousMillis >= 5000)
            {
                currentState = YELLOW_TO_GREEN;

                previousMillis = currentMillis;
            }

            break;

        case YELLOW_TO_GREEN:

            setYellow();
            buzzerOff();

            if (currentMillis - previousMillis >= 5000)
            {
                currentState = GREEN;

                previousMillis = currentMillis;
            }

            break;

        case GREEN:

            setGreen();
            buzzerOff();

            if (currentMillis - previousMillis >= 7000)
            {
                if (pedestrianRequest)
                {
                    currentState = YELLOW_TO_RED;
                }

                else
                {
                    currentState = RED;
                }

                previousMillis = currentMillis;
            }
            break;

        case YELLOW_TO_RED:

            setYellow();
            buzzerOff();

            if (currentMillis - previousMillis >= 5000)
            {
                currentState = RED;

                previousMillis = currentMillis;
            }

            break;

        case PEDESTRIAN:

            setRed();

            if (currentMillis - buzzerMillis >= 500)  // Buzzer toggles every 500 ms
            {
                buzzerState = !buzzerState;

                digitalWrite(BUZZER, buzzerState);

                buzzerMillis = currentMillis;
            }
            // Pedestrian crossing lasts 5 seconds
            if (currentMillis - previousMillis >= 5000)
            {
                buzzerOff();
                buzzerState = false;
                pedestrianRequest = false;
                currentState = GREEN;
                previousMillis = currentMillis;
            }
           break;   
         }
    }