Years = paste('',formatC(2012:2050,width=4,format="d",flag="0"), sep = "")
Seasons = paste("S",formatC(1:52,width=2,format="d",flag="0"), sep = "")
elementsNumb <- length(Years)*length(Seasons)

text <- matrix(NA,elementsNumb,1)
index <- 1
for(y in 1:length(Years)){
  for(s in 1:length(Seasons)){
    text[index,1] <- paste(Years[y],".",Seasons[s],sep = "")
    index <- index +1
  }
}
text.gms <- rbind("/",text,"/;")

setwd("C:/Users/olex/(^_^)/ResLab/Modelling/Balmorels/Balmorel_git/base/AnnotationPlotting")
write.table(text.gms, file = paste("YSMapping.inc",set=""),row.names = F,quote = F, col.names = F)
