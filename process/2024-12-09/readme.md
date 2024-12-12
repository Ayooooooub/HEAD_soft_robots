# Reasearch of the day (TIS BIG)

## Scenario ish

You have your Calystegia that detects movement, but now it might not open or close automatically. Instead, it depends on your care.  

Movement in shared spaces is reflected in color, using either LEDs (less interesting) or thermochromatic ink. The latter would use a Peltier unit to heat the flower's stem and change the color of its paper petals.  

To sum up:  
- You care for the flower with light, like shining your phone flashlight on it occasionally.  
- Movement outside triggers a color change—heating up when someone is there, staying cold when no one is around.  

The clever part is that sometimes you need to check the color, but it’s dark. So, you use your flashlight to see, which in turn “cares” for the flower and makes it “happy.” There’s potential for an interesting cycle here—let’s explore this idea further!  


# OR

I keep the simple interaction with the motion sensor to detect roommates, as already planned. To add complexity without using a ton of sensors, I give the Calystegia personality and more importantly, a network.  

For example: if I have two flowers, one in my room (the "tamed" flower) and one in the common space (the "wild" flower), the wild one sends motion data to the tamed one, so I still know if someone is outside.  

The twist: if I spend too much time outside and the wild flower detects me often, the tamed flower gets "jealous" and starts giving unreliable data. This means I need to spend time with the tamed flower to "fix" it. It can tell me apart from my roommates because it detects me when I'm in my room or I have to actively manifest my presence to it. 

So yeah this can be a way to care and add interactivity with the flower.


So basically I have two arduino boards for my flowers, with 2 motion sensors with two servo motors with twice the effin mecachism that permits it to transform rotaion in linear movement and thats pretty much it. Each has a different code to match utility and "personnality" of the wild and tamed calestygia.