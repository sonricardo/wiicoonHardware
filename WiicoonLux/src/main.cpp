#include <WiFi.h>

const int NFOCOS = 3;
const int FOCOS[3] = { 25, 26, 27 };
const int APAGADORES[3] = { 17, 18, 19 };
int i_Estados[3] = { LOW, LOW, LOW };
int i_Marcadores[3];


void inicializar(){
  for (int i = 0; i < NFOCOS; i++)				// valores iniciales de focos
	{
		pinMode(FOCOS[i], OUTPUT);
		pinMode(APAGADORES[i], INPUT);
		i_Marcadores[i] = digitalRead(APAGADORES[i]);
		//focoAccion(i + 1, EEPROM.read(EE_EF[i]), true);
	}
}
void focoApagador()
{
	for (int i = 0; i < NFOCOS; i++)
	{
		if (i_Marcadores[i] != digitalRead(APAGADORES[i]))
		{
      i_Marcadores[i] = !i_Marcadores[i];
      i_Estados[i] = !i_Estados[i];
      focoAccion(i + 1, i_Estados[i], true);
		}
	}
}
void focoAccion(int i_focoId, int i_focoEst, boolean b_serv)
{
	int i_foco = i_focoId - 1;
	//EEPROM.write(EE_EF[i_foco], i_focoEst);
	//EEPROM.commit();
	i_Estados[i_foco] = i_focoEst;
	digitalWrite(FOCOS[i_foco], i_focoEst);
  Serial.print("Foco: ");
  Serial.print(i_focoId);
  if(i_focoEst == 1)
    Serial.println(" ON");
  else Serial.println(" OFF");
}

void setup() {
  Serial.begin(115200);
  inicializar();
}

void loop() {
  focoApagador());
}       
