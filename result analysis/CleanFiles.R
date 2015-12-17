#rimuove cluster banali

resultDBSCAN <- "~/Desktop/progetto IAC/outputForExcelInters.csv"
howToSave <- "~/Desktop//progetto IAC/outputForExcelIntersNew.csv"

dataUnionOrIntersection <- read.table(resultDBSCAN, header=FALSE, sep=";")

i <- 1

col1 <-c()
col2 <-c()
col3 <-c()
col4 <-c()

flag <-FALSE

#i clusters devono essere unici
for(cluster in dataUnionOrIntersection[,4]){
  
  flag <-FALSE
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  
  contigencyTable <- table(myCluster)
  
  thereIsNoise<-row.names(contigencyTable)[1]
  
  #c'è solo una clasee
  if(length(contigencyTable)!=1){
    
    #se cè un cluster che è maggiore del 70% di tutti
    
    freqRel <- round(contigencyTable/sum(contigencyTable)*100,1)
    
    #se c'è troppo rumore non mi piace...ho messo 30 per cento
    if(thereIsNoise == "0" && freqRel[1]>30)
      flag <- TRUE
      
    
    
    myconditions <- freqRel > 70
    
    for(condition in myconditions){
      if(condition){
        flag <- TRUE
        break
      }
      
    }
    
    if(!flag){
      
      cluster <- as.vector(dataUnionOrIntersection[i,4])
      
      #no cluster ridondanti
      if(length(intersect(cluster,col4))==0){
        col1 <- c(col1,as.vector(dataUnionOrIntersection[i,1]))
        col2 <- c(col2,as.vector(dataUnionOrIntersection[i,2]))
        col3 <- c(col3,as.vector(dataUnionOrIntersection[i,3]))
        col4 <- c(col4,cluster)
      }
        
    }  
    
    
  }
  
  i<- i+1
  print(i)
  
}

df = data.frame(col1, col2, col3,col4)

write.table(df,file = howToSave,sep = ";",col.names = FALSE,row.names = FALSE)