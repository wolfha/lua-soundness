local sdn = require 'soundness'

--
-- sound(frequency, length, volume)
--

sdn.sound(440.00, 1, 0.75)


--
-- pause(length)
--
sdn.pause(0.5)

sdn.sound(261.63, 0.4, 0.75)
sdn.sound(261.63, 0.4, 0.75)
sdn.sound(293.66, 0.4, 0.75)
sdn.sound(329.63, 0.4, 0.75)

sdn.sound(329.63, 0.4, 0.75)
sdn.sound(293.66, 0.4, 0.75)
sdn.sound(261.63, 0.4, 0.75)

sdn.pause(0.6)

--
-- pause(length, volume)
--
sdn.noise(2, 0.3);
