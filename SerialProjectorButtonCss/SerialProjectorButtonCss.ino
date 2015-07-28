void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

Serial.print("<a href=\"http://amperka.ru/\" target=\"_blank\" class=\"myButton\">green</a>");
Serial.print("<style type=\"text/css\">");
Serial.print(".myButton {");
Serial.print("  background-color:#44c767;");
Serial.print("  -moz-border-radius:28px;");
Serial.print("  -webkit-border-radius:28px;");
Serial.print("  border-radius:28px;");
Serial.print("  border:1px solid #18ab29;");
Serial.print("  display:inline-block;");
Serial.print("  cursor:pointer;");
Serial.print("  color:#ffffff;");
Serial.print("  font-family:Arial;");
Serial.print("  font-size:17px;");
Serial.print("  padding:16px 31px;");
Serial.print("  text-decoration:none;");
Serial.print("  text-shadow:0px 1px 0px #2f6627;");
Serial.print("}");
Serial.print(".myButton:hover {");
Serial.print("  background-color:#5cbf2a;");
Serial.print("}");
Serial.print(".myButton:active {");
Serial.print("  position:relative;");
Serial.print("  top:1px;");
Serial.print("}");
Serial.print("</style>");
Serial.print("\n");  

delay(100);
}
