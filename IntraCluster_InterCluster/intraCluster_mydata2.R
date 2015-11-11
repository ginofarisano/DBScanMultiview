library(clusterSim)
library(clv)
cl2 <- pam(mydata2, 4)
cls.scatt.data(mydata2, cl2$clustering, dist="manhattan")
