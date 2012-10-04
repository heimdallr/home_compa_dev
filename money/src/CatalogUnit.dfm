object fmCatalog: TfmCatalog
  Left = 970
  Top = 279
  Width = 467
  Height = 424
  Caption = 'fmCatalog'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object pnlBottom: TPanel
    Left = 0
    Top = 357
    Width = 459
    Height = 37
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      459
      37)
    object btnOk: TBitBtn
      Left = 13
      Top = 8
      Width = 154
      Height = 24
      Action = actOk
      Caption = 'OK'
      Default = True
      TabOrder = 0
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object btnCancel: TBitBtn
      Left = 294
      Top = 8
      Width = 153
      Height = 24
      Action = actCancel
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object pnlMain: TPanel
    Left = 0
    Top = 0
    Width = 459
    Height = 357
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object dbgData: TDBGridEh
      Tag = 1
      Left = 0
      Top = 0
      Width = 459
      Height = 357
      Align = alClient
      AllowedOperations = []
      AutoFitColWidths = True
      ColumnDefValues.Title.Alignment = taCenter
      ColumnDefValues.Title.TitleButton = True
      Ctl3D = False
      DataGrouping.GroupLevels = <>
      DataSource = dsrcData
      DefaultDrawing = False
      Flat = True
      FooterColor = clWindow
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -10
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      IndicatorOptions = [gioShowRowIndicatorEh]
      OddRowColor = 15790320
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      PopupMenu = pmCatalog
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -10
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnDblClick = actOkExecute
      OnDrawColumnCell = dbgDataDrawColumnCell
      OnGetCellParams = dbgDataGetCellParams
      Columns = <
        item
          EditButtons = <>
          FieldName = 'NAME'
          Footers = <>
          Title.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
          Width = 170
        end
        item
          AutoFitColWidth = False
          EditButtons = <>
          FieldName = 'COLOR'
          Footers = <>
          KeyList.Strings = (
            '-1')
          PickList.Strings = (
            #1046#1086#1087#1072)
          TextEditing = False
          Title.Caption = #1062#1074#1077#1090
          Width = 32
        end>
      object RowDetailData: TRowDetailPanelControlEh
      end
    end
  end
  object alMain: TActionList
    Left = 172
    Top = 220
    object actOk: TAction
      Caption = 'Ok'
      ShortCut = 16397
      OnExecute = actOkExecute
    end
    object actCancel: TAction
      Caption = #1047#1072#1082#1088#1099#1090#1100
      ShortCut = 8219
      OnExecute = actCancelExecute
    end
    object actAdd: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1086#1089#1077#1076#1072
      OnExecute = actAddExecute
    end
    object actEdit: TAction
      Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1090#1100
      OnExecute = actEditExecute
    end
    object actDel: TAction
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnExecute = actDelExecute
    end
    object actAddChild: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1090#1086#1084#1082#1072
      OnExecute = actAddChildExecute
    end
    object actCollapse: TAction
      Caption = #1057#1074#1077#1088#1085#1091#1090#1100
      OnExecute = actCollapseExecute
    end
    object actExpand: TAction
      Caption = #1056#1072#1079#1074#1077#1088#1085#1091#1090#1100
      OnExecute = actExpandExecute
    end
    object actLeft: TAction
      Caption = 'actLeft'
      ShortCut = 37
      OnExecute = actLeftExecute
    end
    object actRight: TAction
      Tag = 1
      Caption = 'actRight'
      ShortCut = 39
      OnExecute = actRightExecute
    end
    object actSetColor: TAction
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1094#1074#1077#1090
      OnExecute = actSetColorExecute
    end
    object actUp: TAction
      Tag = -1
      Caption = #1042#1074#1077#1088#1093
      ShortCut = 16422
      OnExecute = actUpExecute
    end
    object actDown: TAction
      Tag = 1
      Caption = #1042#1085#1080#1079
      ShortCut = 16424
      OnExecute = actDownExecute
    end
  end
  object dsdData: TDataSetDriverEh
    ProviderDataSet = dsData
    Left = 108
    Top = 88
  end
  object mtData: TMemTableEh
    FieldDefs = <>
    IndexDefs = <>
    Params = <>
    DataDriver = dsdData
    StoreDefs = True
    TreeList.KeyFieldName = 'id'
    TreeList.RefParentFieldName = 'id_p'
    TreeList.DefaultNodeExpanded = True
    TreeList.FilterNodeIfParentVisible = False
    Left = 80
    Top = 88
  end
  object dsrcData: TDataSource
    DataSet = mtData
    Left = 56
    Top = 88
  end
  object dsData: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 136
    Top = 88
  end
  object pmCatalog: TPopupMenu
    Left = 200
    Top = 220
    object N1: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      object N4: TMenuItem
        Action = actAdd
      end
      object N5: TMenuItem
        Action = actAddChild
      end
    end
    object N2: TMenuItem
      Action = actEdit
    end
    object N11: TMenuItem
      Caption = #1055#1077#1088#1077#1076#1074#1080#1085#1091#1090#1100
      object N12: TMenuItem
        Action = actUp
      end
      object N13: TMenuItem
        Action = actDown
      end
    end
    object N3: TMenuItem
      Action = actDel
    end
    object N6: TMenuItem
      Caption = '-'
    end
    object N7: TMenuItem
      Action = actCollapse
    end
    object N8: TMenuItem
      Action = actExpand
    end
    object N9: TMenuItem
      Caption = '-'
    end
    object N10: TMenuItem
      Action = actSetColor
    end
  end
end
