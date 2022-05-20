import processing.serial.*;

Serial myPort;
Table dataTable;

//keeps track of how many readings you'd like to take before writing the file.
int numReadings = 100; 
//counts each reading to compare to numReadings. 
int readingCounter = 0; 

String fileName;
String val;

boolean end_config = false;
boolean process_data = false;
boolean treat_data = false;
boolean ready_to_send_data = false;

String max_range_string;
String min_range_string;
String string_to_send;

void setup() 
{
  String portName = Serial.list()[0]; 
  myPort = new Serial(this, portName, 115200);
  
  dataTable = new Table();
  
  dataTable.addColumn("id");
  
  dataTable.addColumn("Dedao");
  dataTable.addColumn("Apontador");
  dataTable.addColumn("Dedo do meio");
  dataTable.addColumn("Anelar");
  dataTable.addColumn("Dedinho");
}

void serialEvent(Serial myPort){
  val = myPort.readStringUntil('\n'); 
  if (val!= null && !end_config) { 
  
    val = trim(val); 
    println(val);  

    if(!val.equals("F")){
        int sensorVals[] = int(split(val, ','));
       //for(int i=0; i<5; i++){
       // println(sensorVals[i]); 
       //}
       
        TableRow newRow = dataTable.addRow(); //add a row for this new reading
        newRow.setInt("id", dataTable.lastRowIndex()+1);
  
        newRow.setInt("Dedao", sensorVals[0]);
        newRow.setInt("Apontador", sensorVals[1]);
        newRow.setInt("Dedo do meio", sensorVals[2]);
        newRow.setInt("Anelar", sensorVals[3]);
        newRow.setInt("Dedinho", sensorVals[4]);
        
        readingCounter++; 
        
        print("contador: "); println(readingCounter);
        
        //saves the table as a csv in the same folder as the sketch every numReadings. 
        if (readingCounter % numReadings ==0)
        {
          fileName = str(hour()) + "_" + str(minute()) + "_" + str(second()) + "_" 
          + "dados_sensores_" + str(dataTable.lastRowIndex()+1); 
          saveTable(dataTable, fileName + ".csv"); 
        }
      }else{
        end_config = true ;
      }
   }else{
     if(val!= null){
        val = trim(val); 
        println(val); 
     }
   }
}


void draw()
{ 
   if(end_config && !process_data){
      int nrows = dataTable.getRowCount();
      int ncols = dataTable.getColumnCount();
    
      
      int dedao[] = new int [nrows];
      int apontador[] = new int [nrows];
      int meio[] = new int [nrows];
      int anelar[] = new int [nrows];
      int dedinho[] = new int [nrows];
      
      
      for (int i=0; i< nrows; i++){
          dedao[i] = dataTable.getInt(i,"Dedao");
          apontador[i] = dataTable.getInt(i,"Apontador");
          meio[i] = dataTable.getInt(i,"Dedo do meio");
          anelar[i] = dataTable.getInt(i,"Anelar");
          dedinho[i] = dataTable.getInt(i,"Dedinho");
      }
        
      dedao = sort(dedao);
      apontador = sort(apontador);
      meio = sort(meio);
      anelar = sort(anelar);
      dedinho = sort(dedinho);
      
      int pos_perc_25 = 25*nrows/100;
      int pos_perc_50 = 50*nrows/100;
      int pos_perc_75 = 75*nrows/100;
      
      int perc_25[] = {dedao[pos_perc_25+1], apontador[pos_perc_25+1], 
          meio[pos_perc_25+1], anelar[pos_perc_25+1], dedinho[pos_perc_25+1]};
      int perc_50[] = {dedao[pos_perc_50+1], apontador[pos_perc_50+1], 
          meio[pos_perc_50+1], anelar[pos_perc_50+1], dedinho[pos_perc_50+1]};
      int perc_75[] = {dedao[pos_perc_75+1], apontador[pos_perc_75+1], 
          meio[pos_perc_75+1], anelar[pos_perc_75+1], dedinho[pos_perc_75+1]};
      
      float limite_inferior[] = new float[5];
      float limite_superior[] = new float[5];
      
      for (int i=0; i<5; i++){
        limite_inferior[i]= perc_25[i] - 1.5*(perc_75[i] - perc_25[i]);
        limite_superior[i] = perc_75[i] + 1.5*(perc_75[i] - perc_25[i]);
      }
      
     boolean protecao = false;
      for(int i=0; i<nrows; i++){
        for(int j=1; j<ncols-1; j++){
          if (!protecao ){
            if (dataTable.getInt(i,j) > limite_superior[j-1] || 
                dataTable.getInt(i,j) < limite_inferior[j-1]){
                dataTable.removeRow(i);
                protecao = true;
            }
          }
        }
        if(protecao){
          protecao = false;
          i--;
        }
        nrows = dataTable.getRowCount();
      }
      
      saveTable(dataTable, fileName + "_tratado" + ".csv");
      
      process_data = true;
   }
   
   
   if (process_data){
      int nrows = dataTable.getRowCount();
    
      
      int dedao[] = new int [nrows];
      int apontador[] = new int [nrows];
      int meio[] = new int [nrows];
      int anelar[] = new int [nrows];
      int dedinho[] = new int [nrows];
      
      
      for (int i=0; i< nrows; i++){
          dedao[i] = dataTable.getInt(i,"Dedao");
          apontador[i] = dataTable.getInt(i,"Apontador");
          meio[i] = dataTable.getInt(i,"Dedo do meio");
          anelar[i] = dataTable.getInt(i,"Anelar");
          dedinho[i] = dataTable.getInt(i,"Dedinho");
      }
        
      dedao = sort(dedao);
      apontador = sort(apontador);
      meio = sort(meio);
      anelar = sort(anelar);
      dedinho = sort(dedinho);
      
      int min_range[] = {dedao[0],apontador[0],meio[0],anelar[0],dedinho[0]};
      int max_range[] = {dedao[nrows-1],apontador[nrows-1],meio[nrows-1]
                          ,anelar[nrows-1],dedinho[nrows-1]};
      
     for(int i=0; i<5; i++){
       if(i == 0){
         
           if(min_range[i]<1000){
              min_range_string = "0" + String.valueOf(min_range[i]);
           }else{
              min_range_string = String.valueOf(min_range[i]);
           }
           min_range_string = min_range_string + ",";
           
           if(max_range[i]<1000){
              max_range_string = "0" + String.valueOf(max_range[i]);
           }else{
              max_range_string = String.valueOf(max_range[i]);
           }
           max_range_string = max_range_string + ",";
           
       }else{
         
           if(min_range[i]<1000){
             min_range_string = min_range_string + "0" + String.valueOf(min_range[i]);
           }else{
             min_range_string = min_range_string + String.valueOf(min_range[i]);
           }
           min_range_string = min_range_string + ",";
           
           if(max_range[i]<1000){
             max_range_string = max_range_string + "0" + String.valueOf(max_range[i]);
           }else{
             max_range_string = max_range_string + String.valueOf(max_range[i]);
           }
           max_range_string = max_range_string + ",";
         
       }
     }
     
     //min_range_string = min_range_string + "\n";
     //max_range_string = max_range_string + "\n";
     
      string_to_send = min_range_string + max_range_string + "\n";
      
      ready_to_send_data = true;
   }
   
   if(ready_to_send_data){
      myPort.write(string_to_send);
      //print("mandando: " + string_to_send);
      delay(3000);
   }
   
}
