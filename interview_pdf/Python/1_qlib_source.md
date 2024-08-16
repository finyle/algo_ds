# data
## 1. data.data.DatasetProvider.dataset_processor(instruments_d, column_names, start_time, end_time, freq, inst_processors=[])
### ParallelExt(joblib.Parallel), joblib.delay

## 2. data.storage.file_storage.FileFeatureStorage.write() & __getitem__()

## 3. data.data.ExpressionProvider().get_expressio_instances() -> eval(field)

## 4. data.libs.rolling & expanding 
### Cython

## 5. data.dataset.handler & processor

# ####################################################

# workflow 
## 1. workflow.recorder_temp.SignalRecorder.generate
### model.predict()

## 2. workflow.recorder_temp.PortAnaRecorder.generate
### backtest.normal_backtest() 


# ####################################################

# backtest
## 1. backtest.__init__.backtest -> backtest.collect_data_loop() 
### trade_decision = trade_strategy.generate_from(execute_result) 
### execute_result = yield from trade_executor.collect_data(trade_decision)

# ###########################################################

# contrib.eva.aplpha
## ic
## return 
## auto_corr