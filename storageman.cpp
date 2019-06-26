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
    public partial class skladform : Form
    {
        public skladform()
        {
            InitializeComponent();
        }
 
        private void button1_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(ya.Text))
            {
                using (var db = new DanyaKursa4Entities())
                {
                    var l = (from yas in db.Storage select new { yas.PlaceID, yas.ReagentID, yas.reagents.ReagName, yas.Quantity }).ToList();
                    dataGridView1.DataSource = l;
                    dataGridView1.Refresh();
                }
            }
            else
            {
                int idya = Int32.Parse(ya.Text);
                using (var db = new DanyaKursa4Entities())
                {
                    if (!db.Storage.Any(x => x.PlaceID == idya))
                    {
                        Error a = new Error("Некоректные данные");
                        a.Show();
                    }
                    else
                    {
                        var l = (from ya in db.Storage where ya.PlaceID == idya select new { ya.PlaceID, ya.ReagentID, ya.reagents.ReagName, ya.Quantity }).ToList();
                        dataGridView1.DataSource = l;
                        dataGridView1.Refresh();
                    }
                }
 
            }
        }
 
        private void button2_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(reg.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
            }
            else
            {
                int r = Int32.Parse(reg.Text);
                using (var db = new DanyaKursa4Entities())
                {
                    if (!db.Storage.Any(x => x.ReagentID == r))
                    {
                        Error a = new Error("Реагент не найдет на складе");
                        a.Show();
                    }
                    else
                    {
                        var l = (from ya in db.Storage where ya.ReagentID == r select new { ya.PlaceID, ya.ReagentID, ya.reagents.ReagName, ya.Quantity }).ToList();
                        dataGridView1.DataSource = l;
                        dataGridView1.Refresh();
                    }
                }
            }
        }
 
        private void tabPage1_Click(object sender, EventArgs e)
        {
 
        }
 
        private void label5_Click(object sender, EventArgs e)
        {
 
        }
 
        private void button3_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(idyach.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
            }
            else
            {
                if(String.IsNullOrWhiteSpace(reagn.Text)&& !String.IsNullOrWhiteSpace(kolvo.Text))
                {
                   
                    int q = Int32.Parse(kolvo.Text);
                    int ya = Int32.Parse(idyach.Text);
                   
                    using (var db = new DanyaKursa4Entities())
                    {
                        if(!db.Storage.Any(x => x.PlaceID == ya))
                        {
                            Error a = new Error("Некоректные данные");
                            a.Show();
                        }
                        else
                        {
                            var curr = (from y in db.Storage where y.PlaceID == ya select y).First();
                            curr.Quantity = q;
                            db.Entry(curr).State = System.Data.Entity.EntityState.Modified;
                            db.SaveChanges();
                            var l = (from yas in db.Storage select new { yas.PlaceID, yas.ReagentID, yas.reagents.ReagName, yas.Quantity }).ToList();
                            dataGridView1.DataSource = l;
                            dataGridView1.Refresh();
                            dataGridView2.DataSource = l;
                            dataGridView2.Refresh();
                        }
                    }
                }
                else if(!String.IsNullOrWhiteSpace(reagn.Text)&&!String.IsNullOrWhiteSpace(kolvo.Text))
                {
                    int q = Int32.Parse(kolvo.Text);
                    int ya = Int32.Parse(idyach.Text);
                    int r = Int32.Parse(reagn.Text);
                    using (var db = new DanyaKursa4Entities())
                    {
                        if (!db.Storage.Any(x => x.PlaceID == ya)|| !db.reagents.Any(x => x.ID == r))
                        {
                            Error a = new Error("Некоректные данные");
                            a.Show();
                        }
                        else
                        {
                            var curr = (from y in db.Storage where y.PlaceID == ya select y).First();
                            curr.Quantity = q;
                            curr.ReagentID = r;
                            db.Entry(curr).State = System.Data.Entity.EntityState.Modified;
                            db.SaveChanges();
                            var l = (from yas in db.Storage select new { yas.PlaceID, yas.ReagentID, yas.reagents.ReagName, yas.Quantity }).ToList();
                            dataGridView2.DataSource = l;
                            dataGridView2.Refresh();
                            dataGridView1.DataSource = l;
                            dataGridView1.Refresh();
                        }
                    }
                }
                else if((String.IsNullOrWhiteSpace(reagn.Text) && String.IsNullOrWhiteSpace(kolvo.Text))|| (!String.IsNullOrWhiteSpace(reagn.Text) && String.IsNullOrWhiteSpace(kolvo.Text)))
                {
                    Error a = new Error("Некоректные данные");
                    a.Show();
                }
            }
 
        }
 
        private void ya_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }
    }
}