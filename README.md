# ARC-Ikrea-Pack
Código de arduino para el reactor ARC del Ikrea Pack. Viva Stan Lee.

Si por lo que sea no haces el código tú mismx pero te interesa saber la estrategia utilizada en la siguiente función, se detalla por aquí abajo. Te invito a intentarlo por tu cuenta; la verdad que es entretenido enfrentarse a las unidades de los ángulos...

### Polar Jojaluh
> El nombre es una mezcla de Jojalu, el nombre de la otra función que hace lo mismo (con una `h` al final para que quede peor) y polar porque el principio de funcionamiento son ángulos.

Es una versión del código que hace lo mismo, aunque con la ventaja de la extensibilidad. Es más fácil adaptar el código a un número distinto de ledes, solo habría que cambiar `nLeds` por la cantidad existente. Posiblemente adaptar el rango en el que se encuentran también, modificando el offset de 3 en `analogWrite(led+3, intensity);`. Y si los conectas de una forma más random pues acompañarlo de algún método que permita el redireccionamiento adecuado.

#### ¿Cómo funciona?
Virtualmente podemos pensar que estamos girando un semieje, que respecto del origen tiene un ángulo `axisAngle`. Luego, dentro de `for`, calculamos para cada LED su ángulo respecto del origen. Los suponemos equiespaciados, y que el primero sea el único con el ángulo de 0º.

A continuación calculamos la distancia angular entre el semieje y el ángulo del LED, `ledAngle`. Hay que tener en cuenta los casos en los que el LED está muy próximo al origen y el ángulo del semieje muy cercano a 2PI, y todos los similares para cada LED, por lo que calculamos el menor de las dos distancias en cada sentido.

Posteriormente, solo si nos encontramos dentro de la "media amplitud" que hemos definido, calcularemos el brillo que se debe asignar al LED. Cuando estamos muy próximos al eje, o sea, `angDist` tiende a 0, nuestro brillo debe tender al máximo, y la relación en su pico debería valer 1. Luego lo multiplicamos por 255 para tener un valor PWM que el Arduino pueda asignar, y le adicionamos 0.5 para que redondee al hacer el `static_cast<int>` - la forma bonita de convertir tipos en C++ sin liarla parda.

Si no estaba dentro de esa amplitud pues le asignamos el brillo a cero y se lo pasamos al `analogWrite()` para que se lo ponga al LED del que calculábamos la intensidad. 

Tras pasar por los ledes que hubiesen, adicionamos un pequeño incremento al semieje virtual, esperamos unos milisegundos y volvemos a hacer los cálculos.

##### Ventajas
	- Consiste en un diseño más modular: puedes cambiar fácilmente la cantidad de LEDs y, mientras se cumpla que todos están conectados en puertos consecutivos, el mismo código funciona.
	- La "media amplitud" se puede cambiar al gusto
	- Al manejar ángulos, alterar el código se vuelve un poco más concebible

##### Desventajas
	- Se recalculan los ángulos de cada LED en cada repetición del bucle
	- Si no los tienes conectados consecutivamente te tocará mapear cada `led` a su pin correspondiente

No lo he probado, pero con un `VANG` lo suficientemente pequeño se debería poder prescindir del `delay(DELAY)`, y que el código no tuviese el tiempo de espera muerto si hay otros procesos que hacer.
