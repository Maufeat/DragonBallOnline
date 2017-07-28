using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.Windows.Forms;

namespace MiHaeng4
{
    class ConvertFromRDF
    {
        private enum NodeType
        {
            NODE_TYPE_ID,
            NODE_TYPE_TEXT,
            NODE_TYPE_ETC,
        };

        private NodeType nodeType;

        public ConvertFromRDF()
        {
            nodeType = new NodeType();
            nodeType = NodeType.NODE_TYPE_ETC;
        }
        public bool ConvertToXML(string[] rdfFileNames, string xmlFile)
        {
            FileStream fs = new FileStream(xmlFile, FileMode.Create);
            StreamWriter swXML = new StreamWriter(fs);

            //MH4Global.pgbXML.Maximum = rdfFileNames.Length;
            //MH4Global.pgbXML.Value = 0;

            foreach (string rdfFile in rdfFileNames)
            {
                BinaryReader br = new BinaryReader(File.OpenRead("C:/Wow/Table_MOB_Data.rdf"),Encoding.Unicode );
                int len = (int)br.BaseStream.Length;
                int pos = 0;
                while (pos < len)
                {
                    UInt32 id = br.ReadUInt32();
                    UInt16 lenValue = br.ReadUInt16();
                    string val = br.ReadString();
                
                    swXML.WriteLine(id);
                    swXML.WriteLine(lenValue);
                    swXML.WriteLine(val);
                    pos += sizeof(UInt32);
                    pos += sizeof(UInt16);
                    //pos += System.Runtime.InteropServices.Marshal.SizeOf(val);
                }
         
                br.Close();
                swXML.Close();
                fs.Close();
            }
            // ¼­¹öÀÇ ¿äÃ»À¸·Î ÀÎÇØ¼­ ´õ¹Ì 1 ¹ÙÀÌÆ®¸¦ ³Ö¾îÁØ´Ù
            //bwRDF.Write(new byte[1]);

            /*foreach (string xmlFile in xmlFiles)
            {
                string nakedFileName = Path.GetFileName(xmlFile);
                MH4Global.lbXML.Text = "RDF Converting... : " + nakedFileName;
                MH4Global.lbXML.Update();

                XmlTextReader reader = new XmlTextReader(xmlFile);
                // XMLÀÇ Çì´õÆÄÀÏ ºÎºÐÀº ±×³É ³Ñ±ä´Ù. (·ê¿¡ ¾Èµû¸£°í ÀÖ±â¶§¹®)
                for (int i = 0; i < 12; ++i)
                {
                    reader.Read();
                }

                while (reader.Read())
                {
                    reader.MoveToContent();

                    if (reader.NodeType == XmlNodeType.Element)
                    {
                        if (reader.Name == "F1")
                        {
                            nodeType = NodeType.NODE_TYPE_ID;
                        }
                        else if (reader.Name == "F2")
                        {
                            nodeType = NodeType.NODE_TYPE_TEXT;
                        }
                        else
                        {
                            nodeType = NodeType.NODE_TYPE_ETC;
                        }
                    }
                    else if (reader.NodeType == XmlNodeType.Text)
                    {
                        try
                        {
                            if (nodeType == NodeType.NODE_TYPE_ID)
                            {
                                bwRDF.Write(Convert.ToUInt32(reader.Value));
                            }
                            else if (nodeType == NodeType.NODE_TYPE_TEXT)
                            {
                                bwRDF.Write(Convert.ToUInt16(reader.Value.Length));
                                Byte[] byteText = unicode.GetBytes(reader.Value);
                                bwRDF.Write(byteText, 0, byteText.Length);
                            }
                        }
                        catch
                        {
                            MessageBox.Show("XML ÆÄÀÏÀ» ÆÄ½ÌÁß¿¡ ¿¡·¯°¡ ¹ß»ýÇÏ¿´½À´Ï´Ù." + xmlFile + "(" + reader.LineNumber + ")");
                            break;
                        }
                    }
                }

                reader.Close();

                MH4Global.pgbXML.Value += 1;
            }

            
            */
            return true;           

        }

    }

}