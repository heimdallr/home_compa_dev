object dmReportLauncher: TdmReportLauncher
  OldCreateOrder = False
  Left = 712
  Top = 272
  Height = 150
  Width = 215
  object alMain: TActionList
    Left = 32
    Top = 16
    object actRun: TAction
      Caption = 'actRun'
      OnExecute = actRunExecute
    end
  end
end
