Läs igenom hela uppgiften först innan du börjar!

1. De röda, gröna och blå lysdioderna ska blinka på och av med 2 sekunders tidsfördröjning (alla ska blinka tillsammans och inte individuellt). Använd **millis()** och undvik Busy-Wait-lösningar.

2. Om den röda knappen trycks ned ska den röda lysdioden sluta blinka och istället toggla mellan på/av med hjälp av den röda knappen. Det vill säga, varje gång du trycker på den röda knappen ska lysdioden växla mellan tänd och släckt läge.

3. Samma logik som ovan gäller för den gröna knappen och den gröna lysdioden.

4. För den blå lysdioden gäller samma sak, med undantaget att den är dimbar via en vridpotentiometer. När du trycker på den blå knappen ska lysdioden toggla mellan på och av, och intensiteten på lysdioden ska kunna justeras genom att vrida på potentiometern. Observera att dimningen ska fungera även under blinkningen.

5. Det finns en RGB-lysdiod vars färg ska bestämmas av tre glidpotentiometrar. Varje potentiometer ska styra hur mycket röd, grön respektive blå färg som ska lysa i RGB-lysdioden.

6. Det ska också finnas möjlighet att styra lysdioderna från terminalen. Det ska gå att aktivera/inaktivera knapparna samt vridpotentiometern (dock inte glidpotentiometrarna).  
   Exempel:  
   - `>>disable button 1`  
   - `>>enable button 2`  
   Detta skulle inaktivera möjligheten att toggla lysdioden för knapp 1 och aktivera möjligheten att toggla lysdioden för knapp 2.

7. Det ska även gå att tända och släcka lysdioderna via terminalen samt överskrida vridpotentiometerns inställningar.  
   Exempel:  
   - `LedOn 1`  
   - `LedOn 2`  
   - `LedOff 2`  
   - `LedOff 1`  
   - `LedPower 9`  
   - `LedPower -1`  
   Dessa kommandon skulle först tända lysdiod 1, sedan lysdiod 2, därefter släcka lysdiod 2, sedan släcka lysdiod 1, sedan sätta den blå dimbara lysdioden till intensitet 9 (på en skala 0-10 eller 0-255, valfri skala), och slutligen återaktivera vridpotentiometern.

8. Den gula brytaren är en reset-knapp som vid aktivering återställer programmet till sin ursprungliga konfiguration. Det vill säga, lysdioderna ska återgå till att blinka och alla knappar ska bli aktiverade. **Använd interrupts** för att hantera reset-knappen (polling är inte tillåtet). Du får använda interrupts för de andra knapparna också om du vill, men det är obligatoriskt för reset-knappen.

9. Alla knappar ska vara avstudsade! Det vill säga, använd en mjukvarulösning för att undvika felavläsningar på grund av studsar när knapparna trycks ned eller släpps. Ingen Busy-Wait-lösning är tillåten här heller!
