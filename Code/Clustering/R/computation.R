pp_series <- reinterpolate(pp_data, new.length = max(lengths(pp_data)))
pp_series <- zscore(pp_series)
wp_series <- reinterpolate(wp_data, new.length = max(lengths(wp_data)))
wp_series <- zscore(wp_series)


lapply(pp_series, write, "d:/pp_series.txt", append=TRUE, ncolumns=1000)
lapply(wp_series, write, "d:/wp_series.txt", append=TRUE, ncolumns=1000)