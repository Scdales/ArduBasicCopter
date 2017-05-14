void motorStatus(){
  Serial.print ("Motor Status: ");
  for (int i=0;i<4;i++)
  {
    Serial.print (i+1);
    Serial.print (": ");
    Serial.print (motors[i].status());
    Serial.print (" ");
  }
  Serial.println("");
}

void motorController(int in) {
  switch (in) {
  case 5:
    {
      Serial.println("You got all da motors hynere");
      while (!Serial.available());
      int value = Serial.parseInt();
      for (int i=0;i<4;i++){
        motors[i].speedAdjust(value);
      }
      motorStatus();
      break;
    }
  case 1:
    { 
      Serial.println("Motor Uno...");
      while (!Serial.available());
      int value = Serial.parseInt();
      motors[0].speedAdjust(value);
      motorStatus();
      break;
    }
  case 2:
    { 
      Serial.println("Motor Dos...");
      while (!Serial.available());
      int value = Serial.parseInt();
      motors[1].speedAdjust(value);
      motorStatus();
      break;
    }
  case 3: 
    { 
      Serial.println("Motor Tres...");
      while (!Serial.available());
      int value = Serial.parseInt();
      motors[2].speedAdjust(value);
      motorStatus();
      break;
    }
  case 4:     
    { 
      Serial.println("Motor Quatro...");
      while (!Serial.available());
      int value = Serial.parseInt();
      motors[3].speedAdjust(value);
      motorStatus();
      break;
    }

  }
}
