inherited fmReportTurnover: TfmReportTurnover
  Top = 242
  Caption = #1054#1073#1086#1088#1086#1090#1099
  PixelsPerInch = 96
  TextHeight = 13
  inherited pnlFilter: TPanel
    inherited pnlDateIntervalType: TPanel
      Visible = False
    end
  end
  inherited pnlMain: TPanel
    inherited pnlRes: TPanel
      object Splitter4: TSplitter
        Left = 0
        Top = 469
        Width = 515
        Height = 4
        Cursor = crVSplit
        Align = alBottom
      end
      object pnlData: TPanel
        Left = 0
        Top = 473
        Width = 515
        Height = 301
        Align = alBottom
        TabOrder = 0
        object dbgData: TDBGridEh
          Tag = 1
          Left = 1
          Top = 1
          Width = 513
          Height = 299
          Align = alClient
          AllowedOperations = []
          AutoFitColWidths = True
          Ctl3D = False
          DataGrouping.GroupLevels = <>
          DataSource = dsrcData
          DefaultDrawing = False
          Flat = True
          FooterColor = 11579568
          FooterFont.Charset = DEFAULT_CHARSET
          FooterFont.Color = clWindowText
          FooterFont.Height = -11
          FooterFont.Name = 'MS Sans Serif'
          FooterFont.Style = []
          IndicatorOptions = [gioShowRowIndicatorEh]
          OddRowColor = 15790320
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentCtl3D = False
          PopupMenu = pmData
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          UseMultiTitle = True
          OnDrawColumnCell = dbgDataDrawColumnCell
          OnGetCellParams = dbgDataGetCellParams
          Columns = <
            item
              EditButtons = <>
              FieldName = 'NAME'
              Footers = <>
              Title.Caption = #1057#1090#1072#1090#1100#1103
              Width = 134
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '# ### ##0.00'
              EditButtons = <>
              FieldName = 'SUMMA'
              Footers = <>
              Title.Caption = #1057#1091#1084#1084#1072', '#1088'.'
              Width = 53
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '##0.0'
              EditButtons = <>
              FieldName = 'SUMMA_PCT_PARENT'
              Footers = <>
              Title.Caption = '% '#1086#1090' '#1086#1073#1086#1088#1086#1090#1072' '#1088#1086#1076#1080#1090#1077#1083#1103
              Width = 80
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '##0.0'
              EditButtons = <>
              FieldName = 'SUMMA_PCT_TOTAL'
              Footers = <>
              Title.Caption = '% '#1086#1090' '#1086#1073#1097#1077#1075#1086' '#1086#1073#1086#1088#1086#1090#1072
              Width = 80
            end
            item
              AutoFitColWidth = False
              DisplayFormat = '# ### ##0.00'
              EditButtons = <>
              FieldName = 'SUMMA_AVG'
              Footers = <>
              Title.Caption = #1057#1088#1077#1076#1085#1080#1081' '#1086#1073#1086#1088#1086#1090
              Width = 80
            end
            item
              AutoFitColWidth = False
              EditButtons = <>
              FieldName = 'COLOR'
              Footers = <>
              KeyList.Strings = (
                '-1')
              PickList.Strings = (
                '')
              TextEditing = False
              Title.Caption = #1062#1074#1077#1090
              Width = 33
            end>
          object RowDetailData: TRowDetailPanelControlEh
          end
        end
      end
      object chrtMain: TChart
        Left = 0
        Top = 0
        Width = 515
        Height = 469
        BackWall.Brush.Color = clWhite
        MarginBottom = 0
        MarginLeft = 0
        MarginRight = 0
        MarginTop = 0
        Title.Text.Strings = (
          'TChart')
        Title.Visible = False
        AxisVisible = False
        Legend.Visible = False
        View3D = False
        View3DOptions.Elevation = 315
        View3DOptions.Orthogonal = False
        View3DOptions.Perspective = 0
        View3DOptions.Rotation = 360
        Align = alClient
        BevelOuter = bvNone
        PopupMenu = pmChart
        TabOrder = 1
        AutoSize = True
        OnMouseMove = chrtMainMouseMove
        OnMouseUp = chrtMainMouseUp
        OnResize = chrtMainResize
      end
    end
  end
  inherited alMain: TActionList
    Left = 56
    Top = 164
    object actChangeColor: TAction [3]
      Caption = #1057#1084#1077#1085#1080#1090#1100' '#1094#1074#1077#1090
      OnExecute = actChangeColorExecute
    end
    object actSwitchMark: TAction [4]
      AutoCheck = True
      Caption = #1052#1077#1090#1082#1080
      OnExecute = actSwitchMarkExecute
    end
  end
  object dsrcData: TDataSource
    DataSet = mtData
    Left = 296
    Top = 88
  end
  object mtData: TMemTableEh
    Params = <>
    DataDriver = dsdData
    TreeList.KeyFieldName = 'ID'
    TreeList.RefParentFieldName = 'ID_P'
    TreeList.DefaultNodeExpanded = True
    TreeList.FilterNodeIfParentVisible = False
    Left = 324
    Top = 88
  end
  object dsdData: TDataSetDriverEh
    ProviderDataSet = dsData
    Left = 352
    Top = 88
  end
  object dsData: TClientDataSet
    Aggregates = <>
    IndexFieldNames = 'ord_num'
    Params = <>
    Left = 380
    Top = 88
  end
  object pmChart: TPopupMenu
    Left = 280
    Top = 352
    object N2: TMenuItem
      Action = actSwitchMark
      AutoCheck = True
    end
  end
  object pmData: TPopupMenu
    Left = 512
    Top = 92
    object N1: TMenuItem
      Action = actChangeColor
    end
  end
end
