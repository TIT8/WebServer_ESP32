# WebServer_ESP32

Where it all began! I was working at [Trevi](https://trevivibratori.com/it/), and from this simple code, above a significant abstraction layer like Arduino (a perfect example of using C++ to hide complexities), without understanding what bootloaders, PROGMEM, or RTOS meant, an incredible journey began.

The ESP32 sent an HTML page with a form embedded, allowing the customer to adjust the frequency of the [jumping feeder](https://trevivibratori.com/images/pdf/new_catalog/jf_series.pdf). Consequently, every device connected to the Access Point (AP) created by the ESP32 could manage the JF.

Undoubtedly, the most challenging aspect was dealing with the power electronics required to control the electromagnets (highly inductive) within the JF.   
While I personally find working with electronics more enjoyable than just coding, the intricacies of power electronics cannot be shared on platforms like GitHub (also, the PCB design was not open source for marketing reasons). [^1]

[^1]: Is it the best strategy for "marketing"? In another life I could try to [commoditize my complement](https://gwern.net/complement#:~:text=Joel%20Spolsky%20in%202002%20identified,layers%20by%20dominating%20one%20layer).

<br>

<img src="https://github.com/TIT8/WebServer_ESP32/assets/68781644/f7a5b7f6-f061-4f29-a3f3-7b8beb2059bb" alt="drawing" width="400"/>



