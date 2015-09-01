void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

Serial.print("<button id=\"but\" onclick=\"myFunction()\">Click me</button>");

Serial.print("<script>");
Serial.print("function myFunction() {");
Serial.print("document.body.style.background = 'red';");
Serial.print("}");
Serial.print("</script>");


Serial.print("\n");  

delay(100);
}
