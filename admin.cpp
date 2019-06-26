using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.Entity.Validation;
 
namespace kursa4
{
    public partial class adminform : Form
    {
        public adminform()
        {
            InitializeComponent();
            using (var db = new DanyaKursa4Entities())
            {
                var l = (from o in db.orders select new { o.ID, o.CompanyName, o.TestID, o.tests.TestName, o.IsOrderFullfield, o.DateFullfield }).ToList();
                dataGridView1.DataSource = l;
                dataGridView1.Refresh();
                dataGridView2.DataSource = l;
                dataGridView2.Refresh();
            }
               
        }
 
        private void button1_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(zak.Text) || String.IsNullOrWhiteSpace(idt.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
            }
            else
            {
                string z = zak.Text;
                int t = Int32.Parse(idt.Text);
                using (var db = new DanyaKursa4Entities())
                {
                    if(!db.tests.Any(x => x.ID == t))
                    {
                        Error a = new Error("Некоректные данные");
                        a.Show();
                    }
                    else
                    {
                        orders a = new orders
                        {
                            CompanyName = z,
                            TestID = t,
                            IsOrderFullfield = "No",
                            DateFullfield = DateTime.MinValue
                        };
                        db.orders.Add(a);
                        db.SaveChanges();
                        var l = (from o in db.orders select new { o.ID, o.CompanyName, o.TestID, o.tests.TestName, o.IsOrderFullfield, o.DateFullfield }).ToList();
                        dataGridView1.DataSource = l;
                        dataGridView1.Refresh();
                        dataGridView2.DataSource = l;
                        dataGridView2.Refresh();
                    }
                }
            }
        }
 
        private void button2_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(ord.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
            }
            else
            {
                int id = Int32.Parse(ord.Text);
                using (var db = new DanyaKursa4Entities())
                {
                    if (!db.orders.Any(x => x.ID == id))
                    {
                        Error a = new Error("Некоректные данные");
                        a.Show();
                    }
                    else
                    {
                        var curr = (from y in db.orders where y.ID == id select y).First();
                        curr.IsOrderFullfield = "Yes";
                        curr.DateFullfield = dateTimePicker1.Value;
                        db.Entry(curr).State = System.Data.Entity.EntityState.Modified;
                        db.SaveChanges();
                        var l = (from o in db.orders select new { o.ID, o.CompanyName, o.TestID, o.tests.TestName, o.IsOrderFullfield, o.DateFullfield }).ToList();
                        dataGridView1.DataSource = l;
                        dataGridView1.Refresh();
                        dataGridView2.DataSource = l;
                        dataGridView2.Refresh();
                    }
                }
            }
        }
 
        private void idt_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }
 
        private void button3_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(del.Text))
            {
                Error a = new Error("Некоректные данные");
                a.Show();
            }
            else
            {
                int d = Int32.Parse(delbox.Text);
                using (var db = new DanyaKursa4Entities())
                {
                    if (!db.orders.Any(x => x.ID == d))
                    {
                        Error a = new Error("Некоректные данные");
                        a.Show();
                    }
                    else
                    {
                        var todel = (from o in db.orders where o.ID == d select o).First();
                        db.orders.Remove(todel);
                        db.SaveChanges();
                        var l = (from o in db.orders select new { o.ID, o.CompanyName, o.TestID, o.tests.TestName, o.IsOrderFullfield, o.DateFullfield }).ToList();
                        dataGridView2.DataSource = l;
                        dataGridView2.Refresh();
                        dataGridView1.DataSource = l;
                        dataGridView1.Refresh();
                    }
                }
            }
        }
    }
}