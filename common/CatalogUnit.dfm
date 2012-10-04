object fmCatalog: TfmCatalog
  Left = 521
  Top = 222
  Width = 618
  Height = 419
  Caption = 'fmCatalog'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 120
  TextHeight = 16
  object dbgData: TDBGridEh
    Left = 0
    Top = 0
    Width = 610
    Height = 391
    Align = alClient
    AllowedOperations = [alopUpdateEh]
    ColumnDefValues.Title.Alignment = taCenter
    Ctl3D = False
    DataGrouping.GroupLevels = <>
    DataSource = dsrcData
    Flat = True
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -13
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    HorzScrollBar.Visible = False
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghIncSearch, dghPreferIncSearch, dghDialogFind, dghColumnResize, dghColumnMove, dghExtendVertLines]
    ParentCtl3D = False
    PopupMenu = pmMain
    ReadOnly = True
    RowDetailPanel.Color = clBtnFace
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -13
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = actOkExecute
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
  object dsrcData: TDataSource
    DataSet = dsData
    Left = 24
    Top = 12
  end
  object alMain: TActionList
    Left = 572
    Top = 8
    object actOk: TAction
      Caption = 'OK'
      ShortCut = 16397
      OnExecute = actOkExecute
    end
    object actCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 8219
      OnExecute = actCancelExecute
    end
  end
  object pmMain: TPopupMenu
    Left = 52
    Top = 64
    object miOk: TMenuItem
      Action = actOk
    end
    object miCancel: TMenuItem
      Action = actCancel
    end
  end
  object dsData: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 52
    Top = 12
  end
end
