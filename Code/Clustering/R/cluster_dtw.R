
#dtw euclid
rm(pp_series, pc.dtwlb, rs.Idx, rs, rs.val, i)

# Reinterpolate series to equal length and normalize
pp_series <- reinterpolate(pp_data, new.length = max(lengths(pp_data)))
pp_series <- zscore(pp_series)

pc.dtwlb <- tsclust(pp_series, k = 80L, 
                    distance = "dtw_lb", centroid = "pam", 
                    seed = 3247, trace = TRUE,
                    control = partitional_control(pam.precompute = FALSE),
                    args = tsclust_args(dist = list(window.size = 80L)))

#plot(pc.dtwlb)

#save
rs.Idx<-pc.dtwlb@cluster
rs.val<-pp_series
rs <- list();
for (i in 1:length(rs.Idx)) {
  rs[[i]] <-  c(names(rs.val[i]), rs.Idx[i]) 
}

lapply(rs, write, "d:/projection_profiles_clustering_dtw.txt", append=TRUE, ncolumns=1000)
lapply(pc.dtwlb@centroids, write, "d:/projection_profiles_centroids_dtw.txt", append=TRUE, ncolumns=1000)