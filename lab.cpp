using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
 
namespace kursa4
{
    public partial class labForm : Form
    {
        public labForm()
        {
            InitializeComponent();
            using (var db = new DanyaKursa4Entities())
            {
                var l = (from rs in db.reagents select new { rs.ID, rs.ReagName }).ToList();
                dataGridView2.DataSource = l;
                dataGridView2.Refresh();
 
            }
           
        }
 
        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }
 
        private void button1_Click(object sender, EventArgs e)
        {
            int id = Int32.Parse(SearchID.Text);
            if(id==123)
            {
 
            }
            else
            {
                using (var db = new DanyaKursa4Entities())
                {
                    if ((from t in db.tests where t.ID == id select t).Count() != 0)
                    {
                        var lis = (from te in db.tests
                                  where (te.ID == id)
                                  select new
                                  { te.ID, te.TestName, te.Descr, te.NormID }).FirstOrDefault();
                        Nazv.Text = lis.TestName;
                        Opis.Text = lis.Descr;
                        Nor.Text = (from n in db.testnorms where(n.ID==lis.NormID) select n.TestNorms1).FirstOrDefault().ToString();
                        var reags = (from rs in db.reag_tests where (rs.testID == id) select new
                                  { rs.reagents.ReagName }
                            ).ToList();
                        dataGridView1.DataSource = reags;
                        //var t = (from c in db.Tovar where c.ID == ID select c).First();
                        //TovName.Text = t.Nazvanie.ToString();
                        //int a = t.IDGruppa;
                        //GrName.Text = ((from b in db.Gruppa where b.ID == a select b.Naim).First()).ToString();
                        //MaxKolvo.Text = t.MaxKolvo.ToString();
                        //Ves.Text = t.Ves.ToString();
                        //Shirina.Text = t.Shirina.ToString();
                        //Visota.Text = t.Visota.ToString();
                        //Dlina.Text = t.Dlina.ToString();
                        //Nal.Text = left.ToString();
                    }
                    else
                    {
                        Error tmp = new Error("Товар не найден");
                        tmp.Show();
                    }
 
                }
            }
 
 
        }
 
        private void SearchID_Enter(object sender, EventArgs e)
        {
            if (SearchID.Text == "123")
            {
                SearchID.Text = "";
                SearchID.ForeColor = Color.Black;
            }
        }
 
        private void SearchID_Leave(object sender, EventArgs e)
        {
            if (SearchID.Text == "")
            {
                SearchID.Text = "123";
                SearchID.ForeColor = Color.DarkGray;
            }
        }
 
        private void label5_Click(object sender, EventArgs e)
        {
 
        }
 
        private void label6_Click(object sender, EventArgs e)
        {
 
        }
 
        private void button2_Click(object sender, EventArgs e)
        {
            bool good = true;
            if(String.IsNullOrWhiteSpace(Naz.Text)|| String.IsNullOrWhiteSpace(Ops.Text)|| String.IsNullOrWhiteSpace(nID.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
                good = false;
 
            }
            if(good)
            {
                string n = Naz.Text;
                string o = Ops.Text;
                int norm = Int32.Parse(nID.Text);
                using (var db = new DanyaKursa4Entities())
                {
                    if ((from tn in db.testnorms where tn.ID == norm select tn).Count() == 0)
                    {
                        Error a = new Error("Некоректные данные");
                        a.Show();
                        good = false;
                    }
                    else
                    {
                        tests ntest = new tests
                        {
                            TestName = n,
                            Descr = o,
                            NormID = norm
                        };
                        db.tests.Add(ntest);
                        db.SaveChanges();
                    }
                }
            }
 
               
        }
 
        private void button3_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(idt.Text) || String.IsNullOrWhiteSpace(idr.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
            }
            else
            {
                using (var db = new DanyaKursa4Entities())
                {
                    int test=Int32.Parse(idt.Text);
                    int reg = Int32.Parse(idr.Text);
 
                    if (((from tn in db.tests where tn.ID == test select tn).Count() == 0)|| ((from rn in db.reagents where rn.ID == reg select rn).Count() == 0))
                    {
                        Error a = new Error("Некоректные данные");
                        a.Show();
                    }
                    reag_tests b = new reag_tests
                    {
                        reagID = reg,
                        testID = test
                    };
                    db.reag_tests.Add(b);
                    db.SaveChanges();
                }
            }
        }
    }
}