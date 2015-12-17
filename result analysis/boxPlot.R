plot.boxplot <- function(dataframe,columnNumber,adjustsMin=0,adjustsMax=0,color="green",names,limMin,limMax,labelFlag=TRUE){
  
  #troppi minini e troppi massimi altrimenti
  flagMin=TRUE
  flagMax = TRUE
  myOutlier<-c()
  
  print(summary(dataframe[,columnNumber]))
  
  print(paste("Varianza:",var(dataframe[,columnNumber])))
  
  standardDeviation <- sd(dataframe[,columnNumber])
  
  print(paste("Deviazione standard:", standardDeviation))
  
  print(paste("Coefficiente di variazione:", standardDeviation/abs(mean(dataframe[,columnNumber]))))
  
  myboxplot <- boxplot(dataframe[,columnNumber],main=names,col=color,ylim=c(limMin,limMax),lwd=0.1)
  
  #print all the information in the boxplot
  info <- myboxplot$stats
  outlier <- myboxplot$out
  #row
  numberOfRow <- dim(dataframe)[1]
  
  textMin <-c()
  textMax <-c()
  
  
  #min and max
  for(i in 1:numberOfRow){
    
    
    if(dataframe[i,columnNumber] %in% info){
      #the min
      if(dataframe[i,columnNumber]== info[1]){                           
      
        #more min
        if(labelFlag && flagMin){
          flagMin=FALSE
          textMin <- c(textMin,rownames(dataframe)[i])
        }
        #the max
      } else  if(dataframe[i,columnNumber]== info[5]){
        
        #more max
        if(labelFlag && flagMax){
          flagMax=FALSE
          textMax <- c(textMax,rownames(dataframe)[i])
        }
        
      }
      
    } else if(dataframe[i,columnNumber] %in% outlier){
      #right
      if(labelFlag && !(dataframe[i,columnNumber] %in% myOutlier)){
        myOutlier<-c(myOutlier,dataframe[i,columnNumber])
        text(1,dataframe[i,columnNumber],paste("Outlier: ",rownames(dataframe)[i]),cex=0.4,pos=(i%%4)+1)
        
      }
        
    }
    
    
    
  }
  
  #below
  if(labelFlag){
    text(1,info[1]+ adjustsMin, paste("Min:",textMin),cex=0.4,pos=1)
  }
    
  
  #above
  if(labelFlag){
    text(1,info[5]+ adjustsMax,paste("Max:",textMax),cex=0.4,pos=3)
  }
      
  
  
  myOrder <- order(dataframe[,columnNumber])
  
  if((numberOfRow %% 2)==0){
    if(labelFlag)
      text(1,info[3], paste(rownames(dataframe)[myOrder[numberOfRow/2]],"-",rownames(dataframe)[myOrder[(numberOfRow/2)+1]],"- Median:",info[3]),cex=0.4,pos=3)
  } else {
    if(labelFlag)
      text(1,info[3], paste(rownames(dataframe)[myOrder[round(numberOfRow/2)]],"- Median:",info[3]),cex=0.4,pos=3)
  }
  
  
}

