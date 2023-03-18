package tests;

import java.io.IOException;

class timer
{
    private int seconds;
    private int minutes;
    private int hours;

    public void InitTimer()
    {
        while (hours != 100)
        {
            if (this.seconds == 60)
        {
            minutes++;
        }           
        if (this.minutes == 60)
        {
            hours++;
        }
        try
        {
            Thread.sleep(1000);
            System.out.print(String.format("%d : %d : %d\r", seconds++, minutes, hours));
        }
        catch (InterruptedException err)
        {
            System.out.print("Hello");
        }
        }
}
}

class Start_Timer 
{
    public final static void main(String args[])
    {
        timer t = new timer();
        t.InitTimer();
    }
}
