library(clusterSim)
library(rgl)
source("clustering_summary.R")
source("findCenter.R")

library(clv)

#per il single view eseguire solo il plot finale (line plot)

####################### MODIFICARE QUESTI PARAMETRI PER ESEGUIRE L'ANALISI SU DATI DIFFERENTI ######################

#dataset iniziale
#correlation1
#dataset1 <- "~/Desktop/progetto IAC/kmeans_miRNASeq_centers.txt"
#correlation2
dataset1 <- "~/Desktop/progetto IAC/kmeans_miRNA_centers.txt"

#dove stampo i risultati?
pathOutputPDF = "~/Desktop/progetto IAC/singleView correlation2/"

resultDBSCAN <- "~/Desktop/progetto IAC/outputSingleViewCorrelation2.csv"



minPTSStart = 4
minPTSStop = 25

#eps1 CAMBIARE SE I VALORI CAMBIANO
x = seq(0.4,0.98,0.01)
#eps2 CAMBIARE SE I VALORI CAMBIANO
y = seq(0.4,0.98,0.01)

#da dove cominciare a mettere i dati su più livelli nel contour plot?
distData<-5

####################### MODIFICARE QUESTI PARAMETRI PER ESEGUIRE L'ANALISI SU DATI DIFFERENTI ######################

####################### READ DATA ######################

mydata1 = read.table(dataset1)
mydata1 = scale(mydata1)
#trasposta della matrice
mydata1 <- t(mydata1)
#trasformo in un dataframe
mydata1<-as.data.frame(mydata1)
View(mydata1)

#leggo i risultati dell'unione o intersezione
dataUnionOrIntersection <- read.table(resultDBSCAN, header=FALSE, sep=";")

#prendo la quarta colonna che sono i clusters
clustersUnionOrIntersection <- dataUnionOrIntersection[,4]

#ogni iterazione dell'algoritmo corrisponde ad una coppia eps1 e eps2
iterationStart = 1
iterationStop = length(clustersUnionOrIntersection)

#altre colonne
eps1Iteration <- dataUnionOrIntersection[,1]
eps2Iteration <- dataUnionOrIntersection[,2]
minPtsIteration <- dataUnionOrIntersection[,3]
#altre colonne


numberOfIterations=length(dataUnionOrIntersection[,4])

####################### READ DATA ######################

####################### CALCOLO MASSIMO NUMERO DI CLUSTER ######################
maxMy<--1

#massimo numero di cluster nel clustering
for(cluster in clustersUnionOrIntersection){
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  
  #metto delle label->vedi cl1$clustering in Example1 in http://artax.karlin.mff.cuni.cz/r-help/library/clusterSim/html/index.DB.html
  myCluster <- setNames(myCluster, 1:length(myCluster))
  
  myMax<-length(table(myCluster))
  
  if(myMax>maxMy)
    maxMy<-myMax
  
}


####################### CALCOLO MASSIMO NUMERO DI CLUSTER ######################

####################### CALCOLO ANGELA INDEX ######################

#SE C'E' TROPPO RUMORE O CI SONO CLUSTER TROPPO GRANDI METTO -10 CON VALORE DI DB
#stampo i risultadi del DB index
result <- c()

i = 1

pb = txtProgressBar(min = 1, max = length(clustersUnionOrIntersection),style = 3)

#first dataset
for(cluster in clustersUnionOrIntersection){
  
  flag <-FALSE
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  
  #metto delle label->vedi cl1$clustering in Example1 in http://artax.karlin.mff.cuni.cz/r-help/library/clusterSim/html/index.DB.html
  myCluster <- setNames(myCluster, 1:length(myCluster))
  
  contigencyTable <- table(myCluster)
  
  thereIsNoise<-row.names(contigencyTable)[1]
  
  #c'?? solo una clasee
  if(length(contigencyTable)!=1){
    
    #se c?? un cluster che ?? maggiore del 70% di tutti
    
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
      
      #index.AngelaIndex (il cluster 0 è rumore pertanto aggiungo sempre +1-> a index.AngelaIndex altrimenti non gli piace)
      index_res = clustering_summary(mydata1, myCluster+1,as.numeric(maxMy))
      
      #metto l'indice in un lista
      result <- c(result,index_res[5])
    } else {
      #clusteroni o troppo rumore
      result <- c(result,-10)
    }
    
    
  } else { #if(length(contigencyTable)!=1)
      #solo un cluster
      result <- c(result,-10)
  }

  setTxtProgressBar(pb,i)
  i = i+1
}

close(pb)

####################### CALCOLO ANGELA INDEX ######################

####################### DISEGNO CONTOURPLOT  ######################


# minPTS
z = seq(minPTSStart,minPTSStop,1)

finalMatrix<-matrix(1,nrow=length(x),ncol=length(y)*length(z),byrow = TRUE)

rowStart = 1
rowEnd = length(x)
colStart= 1
colEnd= length(y)



# add lines 
for (i in minPTSStart:minPTSStop) {
  
  myCounter <- 1
  
  indexMinPts <- which(minPtsIteration==paste("minPts=",i,sep = ""))
    
  for(row in rowStart:rowEnd){
    for(col in colStart:colEnd){
      
        finalMatrix[row,col] = result[indexMinPts[myCounter]]
        #finalMatrix[row,col] = paste(eps1Iteration[indexMinPts[cont]],eps2Iteration[indexMinPts[cont]],minPtsIteration[indexMinPts[cont]])
        
        myCounter= myCounter+1

    }
  }

  colStart= colEnd +1
  colEnd= colEnd + length(y)

} 

rownames(finalMatrix) <- x

labelsColumns <- c()

for(zLab in z){
  for(ylab in y){
    labelsColumns<-c(labelsColumns,paste(ylab,"minPts=",zLab))
  }
}


colnames(finalMatrix) <- labelsColumns

#postprocessing 
#taglio tutte le righe che presentano tutti i valori uguali (ci sono delle combinazioni di eps1 eps2 che presentano sempre valori "cattivi")

rowToDelete <-c()

for(row in 1:length(x)){
  
  myconditions<-finalMatrix[row,]==-10
  
  flag <- TRUE
  
  for(condition in myconditions){
    if(!condition){
      flag <- FALSE
      break
    }
  }
  if(flag){
    rowToDelete<-c(rowToDelete,row)
  }  
    
  
}

finalMatrix <- finalMatrix[-rowToDelete,]

colToDelete <-c()

for(col in 1:(length(y)*length(z))){
  
  myconditions<-finalMatrix[,col]==-10
  
  flag <- TRUE
  
  for(condition in myconditions){
    if(!condition){
      flag <- FALSE
      break
    }
  }
  if(flag){
    colToDelete<-c(colToDelete,col)
  }  
    
}

finalMatrix <- finalMatrix[,-colToDelete]

minValue<-min(finalMatrix[which(finalMatrix!=-10)])
maxValue<-max(finalMatrix)
#faccio 4 range
DeltaDiff<-(maxValue-minValue)/10

col<-c()

#modificare anche la legenda se si modifica qua

#do un peso più alta (altezza maggiore) agli indici migliori

index1<-which(finalMatrix>=(minValue) & finalMatrix<=(minValue+DeltaDiff))

index2<-which(finalMatrix>(minValue+DeltaDiff) & finalMatrix<=(minValue+DeltaDiff*2))

index3<-which(finalMatrix>(minValue+DeltaDiff*2) & finalMatrix<=(minValue+DeltaDiff*3))

index4<-which(finalMatrix>(minValue+DeltaDiff*3) & finalMatrix<=(minValue+DeltaDiff*4))

index5<-which(finalMatrix>(minValue+DeltaDiff*4) & finalMatrix<=(minValue+DeltaDiff*5))

index6<-which(finalMatrix>(minValue+DeltaDiff*5) & finalMatrix<=(minValue+DeltaDiff*6))

index7<-which(finalMatrix>(minValue+DeltaDiff*6) & finalMatrix<=(minValue+DeltaDiff*7))

index8<-which(finalMatrix>(minValue+DeltaDiff*7) & finalMatrix<=(minValue+DeltaDiff*8))

index9<-which(finalMatrix>(minValue+DeltaDiff*8) & finalMatrix<=(minValue+DeltaDiff*9))

index10<-which(finalMatrix>(minValue+DeltaDiff*9) & finalMatrix<=(minValue+DeltaDiff*10))


finalMatrix[index1]=finalMatrix[index1]
finalMatrix[index2]=finalMatrix[index2]*2
finalMatrix[index3]=finalMatrix[index3]*3

finalMatrix[index4]=finalMatrix[index4]*(4*2)
finalMatrix[index5]=finalMatrix[index5]*(5*2)
finalMatrix[index6]=finalMatrix[index6]*(6*2)

finalMatrix[index7]=finalMatrix[index7]*(7*2.5)
finalMatrix[index8]=finalMatrix[index8]*(8*2.5)
finalMatrix[index9]=finalMatrix[index9]*(9*2.5)
finalMatrix[index10]=finalMatrix[index10]*(10*2.5)


x <- 1:nrow(finalMatrix)
y <- 1:ncol(finalMatrix)

zlim <- range(finalMatrix)
zlen <- zlim[2] - zlim[1] + 1

colorlut <- terrain.colors(zlen,alpha=1) # height color lookup table

col <- colorlut[ finalMatrix-zlim[1]+1 ] # assign colors to heights for each point

open3d()

rgl.surface(x, y, finalMatrix, color=col, alpha=0.75, back="lines")

# add titles
title3d('', 'eps2', '', '', 'eps1',col="black")

my.minPts<-c(4)
my.ticks<-c(1)

#assegno tick
for(i in 1:length(y)){
  mySplit<-strsplit(colnames(finalMatrix)[i], " ")[[1]]
  
  thirdMinPts <- as.numeric(mySplit[3])
  
  if(my.minPts[length(my.minPts)]!=thirdMinPts){
    
    segments3d(c(x[1],x[length(x)]),c(-10,-10),c(i,i),col="black")
    
    my.minPts<-c(my.ticks,thirdMinPts)
    my.ticks<-c(my.ticks,i)
  }
   
}


#minPTS1
#se non sono compatti li distanzio per bene
axis3d('z', at=my.ticks, labels="",col="black")

#minPTS2
howManyTicksAndLabels<-1
myLabelX<-seq(1,length(x),howManyTicksAndLabels)
axis3d('x',at=seq(1,length(x),howManyTicksAndLabels),labels ="" ,cex=0.6,col="black")
mtext3d(paste(rownames(finalMatrix)[myLabelX]), at=seq(1,length(x),howManyTicksAndLabels),edge='x', line=0.5,cex=0.6,col="black")


# axis3d('y',at=-10,cex=2,col="white",labels = "",line = 1)
# axis3d('y',at=1,cex=2,col="yellow",labels = "",line = 5)
# axis3d('y',at=2,cex=2,col="orange",labels = "",line = 1)
# axis3d('y',at=3,cex=2,col="red",labels = "",line = 5)
# axis3d('y',at=max(finalMatrix),cex=2,col="black",labels = "",line = 1)


# if(value==-10)
#   col<-c(col,"white")
# if(value>0 && value<1)
#   col<-c(col,"yellow")
# if(value>1 && value<2)
#   col<-c(col,"orange")
# if(value>2 && value<3)
#   col<-c(col,"red")
# if(value>3)
#   col<-c(col,"black")


#box3d(col="black")

#fino a dove si vogliono visualizzare i dati su un solo livello?
#MODIFICARE OGNI VOLTA QUESTO PARAMETRO PERCHE' DIPENDE MOLTO DALL'ESPERIMENTO
mtext3d(paste(colnames(finalMatrix)[my.ticks[1:distData]]), at=my.ticks[1:distData], edge='z', line=0.5,cex=0.6,col="black")


#se sono molto compatti li metto su linee diverse
#fino a dove si vogliono visualizzare i dati su un solo livello?
#MODIFICARE OGNI VOLTA QUESTO PARAMETRO PERCHE' DIPENDE MOLTO DALL'ESPERIMENTO
for(i in (distData+1):length(my.ticks)){
  if(i%%10==0){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=1,cex=0.6,col="black")
  }
      
  if(i%%10==1){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=3,cex=0.6,col="black")
      }
      
  if(i%%10==2){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=5,cex=0.6,col="black")
    }
    
  if(i%%10==3){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=7,cex=0.6,col="black")
     }

  if(i%%10==4){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=9,cex=0.6,col="black")
    }
    
  if(i%%10==5){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=11,cex=0.6,col="black")
    }
   
  if(i%%10==6){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=13,cex=0.6,col="black")
     }
    
  if(i%%10==7){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=15,cex=0.6,col="black")
      }
   
  if(i%%10==8){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=17,cex=0.6,col="black")
      }
    
  if(i%%10==9){
    mtext3d(paste(colnames(finalMatrix)[my.ticks[i]]), at=my.ticks[i], edge='z', line=19,cex=0.6,col="black")
    
  }
    
}

#legend3d("topright", c("DB: 0 to 1 ","DB: 1 to 2 ","DB: 2 to 2.5 ","DB: 2.5 to 3 ","DB: 3 to 4 ","DB: 4 to 5 ","DB: >5"), pch = 15,col=c("yellow","orange","red","blue","green","violet","black"),cex=2)


writeOBJ(paste(pathOutputPDF,"modelloAngela.obj",sep = ""),withTextures = TRUE)

#rgl.postscript( paste(pathOutputPDF,"provaUnity2",sep = ""), fmt = "pgf", drawText = TRUE )
####################### DISEGNO CONTOURPLOT  ######################

####################### DISEGNO PLOT WITH LINE  ######################

#VUOI PLOTTARE DA UN CERTO PUNTO IN POI (a livello di iterazioni del DBSCAN)? 
starPlot<-1001
endPlot<-length(result)

#quante labels
deltaLabel<-50

# get the range for the x and y axis 
xrange <- range(starPlot,endPlot)

indexGood<-which(result!=-10)

yrange <- range(min(result[indexGood]),max(result))

pdf(paste(pathOutputPDF,"andamentoMinPts",".pdf",sep = ""))

#andamento indici DB
plot(xrange,yrange,ylab="Angela's+++ && Gino's+--- Index",xlab="",main="Angela's+++ && Gino's+--- Index",type="n",xaxt="n")

minPTS1 = dataUnionOrIntersection[,1]

minPTS2 = dataUnionOrIntersection[,2]

myLabels1=seq(starPlot,endPlot,deltaLabel)

original.parameters<-par()

axis(1, at=myLabels1,labels=rep("",length(myLabels1)),
     col.axis="blue", las=2, cex.axis=0.7, tck=-.01)

text(myLabels1, par("usr")[3] -0.003, labels = minPTS1[myLabels1], srt = 45, pos = 1, xpd = TRUE,cex = 0.7)
text(myLabels1, par("usr")[3]-0.0065 , labels = minPTS2[myLabels1], srt = 45, pos = 1, xpd = TRUE,,cex = 0.7)


colors <- rainbow((minPTSStop-minPTSStart)+1) 

plotchar <- seq(1,(minPTSStop-minPTSStart)+1,1)

linetype <- rep(1,(minPTSStop-minPTSStart)+1)


# add lines 
for (i in minPTSStart:minPTSStop) {
  
  #li seleziono per minPts
  indexMinPts <- which(dataUnionOrIntersection[,3]==paste("minPts=",i,sep = ""))
  
  

    x<-indexMinPts[seq(1,length(indexMinPts),1)]
    
    y<-result[indexMinPts[seq(1,length(indexMinPts),1)]]
    
    #per non appesantire il grafico levo i risultati che non mi piacciono
    
    indexGoodY<-which(y!=-10)
    
    lines(x[indexGoodY],y[indexGoodY], type="b", lwd=1.5,
          lty=1, col=colors[(i-minPTSStart)+1],pch=plotchar[(i-minPTSStart)+1]) 
  
} 

# add a legend 
legend("topleft", yrange[2]+0.1, paste("MinPts",minPTSStart:minPTSStop), cex=0.5, col=colors,pt.cex = 1,pch=plotchar, lty=1, text.font=4)

dev.off()

####################### DISEGNO PLOT WITH LINE  ######################





