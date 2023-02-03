# ESP32 Thermometer

## Lessons learned

### DHT11 Reset

If you see something like this `Failed to read from DHT sensor!`, you've probably
stumbled upon one of the many pages sharing the same example code on reading
measurements from the DHT11 sensor. What these don't tell you is how to re-establish
the connection to the sensor so you can fix those `nan` readings. This only
applies on the situation when your board suddenly stops showing the measured values
and starts displaying `nan`.

If your code never displayed any measurements and started with `nan`, there are
[other sources to consult](https://randomnerdtutorials.com/solved-dht11-dht22-failed-to-read-from-dht-sensor/).

And now to the solution, I'm not sure it covers all possible situations, but it
has worked as a charm for me so far:

```C
if (isnan(humidity) || isnan(temperature)) {
  dht.begin();
}
```

Yes, that seems to be it, simply try restarting the connection to the sensor using
`dht.begin()`.

Tested by unplugging and re-plugging the sensor.
