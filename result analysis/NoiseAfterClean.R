
resultDBSCAN <- c("outputForExcelUnionNew.csv","outputForExcelIntersNew.csv","outputSingleViewCorrelation1New.csv","outputSingleViewCorrelation2New.csv")

numberOfOsservation<-c()
noiseResult<-c()
numBerOfClusterResult<-c()



for(result in resultDBSCAN){
  
  print(result)
  
  dataUnionOrIntersection <- read.table(result, header=FALSE, sep=";")
  
  i<-0
  totalNoise<-0
  numBerOfCluster<-0
  
  
  for(cluster in dataUnionOrIntersection[,4]){
    
    #trasformo lista di stringhe del tipo "1" "0"... in 1 0
    myCluster <- as.integer(unlist(strsplit(cluster," ")))
    
    contigencyTable <- table(myCluster) 
    
    thereIsNoise<-row.names(contigencyTable)[1]
    
    myNumBerOfCluster<-length(contigencyTable)
    
    numBerOfCluster<-numBerOfCluster+myNumBerOfCluster
    
    if(thereIsNoise == "0")
      totalNoise<-totalNoise+(contigencyTable[1]/sum(contigencyTable))
    i<-i+1
  }
  
  print((totalNoise/i))
  
  numberOfOsservation<-c(numberOfOsservation,i)
  noiseResult<-c(noiseResult,(totalNoise/i))
  numBerOfClusterResult<-c(numBerOfClusterResult,(numBerOfCluster/i))
  
  
  
}

rownames(numberOfOsservation)<-c("Multiview union","Multiview intersection","Singleview miRNASeq","Singleview miRNA")

pdf(paste("numberOfOsservation",".pdf",sep = ""))

bp<-barplot(numberOfOsservation,col = rainbow(length(numberOfOsservation)),names.arg = c("MV union","MV intersection","SV miRNASeq","SV miRNA"),ylim = c(0,200),ylab="Numero di cluster",main="Numero di cluster post-processing")
text(x=bp,numberOfOsservation,labels=numberOfOsservation,pos=3)
dev.off()

pdf(paste("noiseResult",".pdf",sep = ""))

bp<-barplot(noiseResult,col = rainbow(length(noiseResult)),names.arg = c("MV union","MV intersection","SV miRNASeq","SV miRNA"),ylab="Numero di cluster",main="Rumore medio per osservazione",ylim = c(0,0.3))
text(x=bp,noiseResult,labels=round(noiseResult,digits = 2),pos=3)
dev.off()

pdf(paste("numBerOfClusterResult",".pdf",sep = ""))

bp<-barplot(numBerOfClusterResult,col = rainbow(length(numBerOfClusterResult)),names.arg = c("MV union","MV intersection","SV miRNASeq","SV miRNA"),ylab="Numero di cluster",main="Numero di classi medie per osservazione",ylim = c(0,6))
text(x=bp,numBerOfClusterResult,labels=round(numBerOfClusterResult,digit=2),pos=3)
dev.off()

