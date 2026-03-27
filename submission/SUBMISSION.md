## Tinkercad Circuit Link

```
https://www.tinkercad.com/things/hicKVTlOgNJ-terrific-fyyran-borwo/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=bJj9ES8dsHtZhK-3XMb5opYSAW9_lS8HnqSe8hWGNjU
```

## Changes
I added the pulse, so now the LED fades.

I added the feedback led flashing, according to the spec.

I added comments and documentation.

Improved the overall UX for example
 - I r&d'd feedback timings to see what is most understandable
 - I capped the brightness at 68, so the led pulses between 0 and 68, so that when it turns on at full brightness it is distinct. It should ideally be even more distinct, however, lowering the brightness is one of the solutions I could come up with while remaining within the spec


## Program Explanation
The program initializes the LED and button pins, sets up serial tracking, and uses an unconnected analog pin to read environmental electrical noise. This creates a truly random seed, ensuring the game's wait times are unpredictable every time it boots. When the user presses the button to start, a brief delay provides a grace period to prevent accidental double-clicks before calculating a random wait time between two and ten seconds.

During the armed phase, the program uses a non-blocking timer instead of a standard delay. This allows the system to actively listen for early button presses while simultaneously fading the LED up and down to indicate it is waiting. The maximum brightness of this pulse is mathematically capped at 68 out of 255. This ensures the dim waiting pulse is distinctly different from the full-brightness signal. If a user clicks early, the system registers a false start, flashes a penalty warning, and resets.

If the user waits successfully, the LED snaps to maximum brightness as the starting signal. The program records the exact millisecond and traps the system in a loop until the button is pressed, allowing it to accurately calculate the reaction speed. Finally, it logs the attempt count and running average to the serial monitor, and provides immediate gamified feedback by flashing the LED at varying speeds based on the user's performance before resetting for the next round. 

This was an extremely refreshing and enjoyeable simple project after a long time. 

As per the spec the fast and medium responses are below 350ms, which in my experience is too quick given the lags on our computers and tinkercad browser (Or I am just slow :-(   ), given the freedom, I would increase those times. As well as that, there is an unending potential of functionality that could be added here, an LCD display, audio feedback, gameified high score memory, data & analytics and so much more.
